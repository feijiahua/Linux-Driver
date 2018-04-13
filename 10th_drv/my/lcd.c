#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/div64.h>

#include <asm/mach/map.h>
#include <asm/arch/regs-lcd.h>
#include <asm/arch/regs-gpio.h>
#include <asm/arch/fb.h>


#define LCD_SCR_XSIZE	(480)
#define LCD_SCR_YSIZE	(640)

static struct fb_info *s3c_lcd;

struct lcd_regs{
	unsigned long lcdcon1;
	unsigned long lcdcon2;
	unsigned long lcdcon3;
	unsigned long lcdcon4;
	unsigned long lcdcon5;
	unsigned long lcdsaddr1;
	unsigned long lcdsaddr2;
	unsigned long lcdsaddr3;
	unsigned long redlut;
	unsigned long greenlut;
	unsigned long bluelut;
	unsigned long reserved[9];
	unsigned long dithmode;
	unsigned long tpal;
	unsigned long lcdintpnd;
	unsigned long lcdsrcpnd;
	unsigned long lcdintmsk;
	unsigned long lpcsel;
};


static unsigned long *gpbcon;
static unsigned long *gpbdat;
static unsigned long *gpccon;
static unsigned long *gpdcon;
static unsigned long *gpgcon;
static volatile struct lcd_regs *lcd_regs;
static u32 pseudo_palette[16];


/* from pxafb.c */
static inline unsigned int chan_to_field(unsigned int chan, struct fb_bitfield *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	return chan << bf->offset;
}


static int s3c_lcdfb_setcolreg(unsigned int regno, unsigned int red,
			     unsigned int green, unsigned int blue,
			     unsigned int transp, struct fb_info *info)
{
	unsigned int val;
	
	if (regno > 16)
		return 1;

	/* 用red,green,blue三原色构造出val */
	val  = chan_to_field(red,	&info->var.red);
	val |= chan_to_field(green, &info->var.green);
	val |= chan_to_field(blue,	&info->var.blue);
	
	//((u32 *)(info->pseudo_palette))[regno] = val;
	pseudo_palette[regno] = val;

	return 0;
}


static struct fb_ops s3c_lcdfb_ops = {
	.owner		= THIS_MODULE,
	.fb_setcolreg	= s3c_lcdfb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
};



static int lcd_init(void)
{
	/* 分配一个fb_info */
	s3c_lcd = framebuffer_alloc(0, NULL);
	/* 2.设置 */
	/* 2.1 设置固定的参数 */
	strcpy(s3c_lcd->fix.id, "mylcd");
	s3c_lcd->fix.smem_len = LCD_SCR_XSIZE * LCD_SCR_YSIZE * 16/8;	//16 = 5 + 6 + 5, R:5位，G:6位，B:5位 smem_len表示显存长度，以bit位为单位
	s3c_lcd->fix.type = FB_TYPE_PACKED_PIXELS;//类型
	s3c_lcd->fix.visual = FB_VISUAL_TRUECOLOR;//画面类型:真彩色
	s3c_lcd->fix.line_length = LCD_SCR_XSIZE * 2;//一行有240个像素，一个像素16位，也就是2个字节
		
	/* 2.2 设置可变的参数 */
	s3c_lcd->var.xres           = LCD_SCR_XSIZE;
	s3c_lcd->var.yres           = LCD_SCR_YSIZE;
	s3c_lcd->var.xres_virtual   = LCD_SCR_XSIZE;
	s3c_lcd->var.yres_virtual   = LCD_SCR_YSIZE;
	s3c_lcd->var.bits_per_pixel = 16;

	/* RGB:565,设置R,G,B数据在两个字节中存放的位置、长度等 */
	s3c_lcd->var.red.offset		= 11;
	s3c_lcd->var.red.length		= 5;

	s3c_lcd->var.green.offset	= 5;
	s3c_lcd->var.green.length	= 6;

	s3c_lcd->var.blue.offset	= 0;
	s3c_lcd->var.blue.length	= 5;

	s3c_lcd->var.activate		= FB_ACTIVATE_NOW;
	
	
	/* 2.3 设置操作函数 */
	s3c_lcd->fbops= &s3c_lcdfb_ops;
	
	/* 2.4 其他设置 */
	s3c_lcd->pseudo_palette = pseudo_palette;
	//s3c_lcd->screen_base  = ;  /* 显存的虚拟地址 */ 
	s3c_lcd->screen_size   = LCD_SCR_XSIZE * LCD_SCR_YSIZE * 16/8;

	/* 3. 硬件相关的操作 */
	/* 3.1 配置GPIO用于LCD */
	gpbcon = ioremap(0x56000010, 8);
	gpbdat = gpbcon + 1;
	gpccon = ioremap(0x56000020, 4);
	gpdcon = ioremap(0x56000030, 4);
	gpgcon = ioremap(0x56000060, 4);

	*gpccon  = 0xaaaaaaaa;   // GPIO管脚用于VD[7:0],LCDVF[2:0],VM,VFRAME,VLINE,VCLK,LEND 
	*gpdcon  = 0xaaaaaaaa;   // GPIO管脚用于VD[23:8]
	*gpbcon &=~ (3);
	*gpbcon |= 1;
	*gpbdat &= ~1;     /* 输出低电平 */

	*gpgcon |= (3<<8);	/* GPG4用作LCD_PWREN */
	
	/* 3.2 根据LCD手册设置LCD控制器，比如VCLK的频率等 */
	lcd_regs = ioremap(0x4d000000, sizeof(struct lcd_regs));

	/* bit[17:8]: VCLK = HCLK / [(CLKVAL + 1) * 2], lcd手册P14;
	 * 			  10MHz(100ns) = 100MHz / [(CLKVAL + 1) * 2];
	 *			  CLKVAL = 4;
	 * bit[6:5] : 0b11, TFT LCD
	 * bit[4:1] : 0b1100, 16 bpp for TFT
	 * bit[0]   : 0 = Disable the video output and the LCD control signal.
	 */
	lcd_regs->lcdcon1 = (4 << 8) | (3 << 5) | (0x0c << 1);

	/* 垂直方向时间参数 
	 * bit[31:24]: VBPD, VSYNC之后再过多长时间才能发出第一行数据
	 * 			   LCD手册 T0 - T2 - T1 = 4;
	 *             VBPD = 3;
	 * bit[23:14]: 一帧数据有多少行，320行，所以LINEVAL = 320 - 1 = 319;
	 * bit[13:6] : VFPD，发出最后一行数据之后，再过多少时间发出VSYNC信号
	 * 			   LCD手册 T2 - TY5 = 322 - 320 = 2，所以VFPD = 2 - 1 = 1;
	 * bit[5:0]  : VSPW, VSYNC信号的脉冲宽度
	 *			   LCD手册 T1 = 1，所以VSPW = 1 - 1 = 0;
	 */
	lcd_regs->lcdcon2 = (3 << 24) | (319 << 14); (1 << 6) | (0 << 0);

	/* 水平方向时间参数  
	 * bit[25:19]: HBPD, HSYNC之后再过多长时间才能发出第一个像素的数据
	 * 			   LCD手册 T6 - T7 - T8 = 17;
	 *             HBPD = 16;
	 * bit[18:8]: 一行有多少个像素，240行，所以HOZAL = 240 - 1 = 239;
	 * bit[7:0] : HFPD，发出一行中最后一个像素之后，再过多少时间发出HSYNC信号
	 * 			   LCD手册 T8 - TY11 = 251 - 240 = 11，所以VFPD = 11 - 1 = 10;
	 * LCDCON4
	 * bit[7:0]  : HSPW, HSYNC信号的脉冲宽度
	 *			   LCD手册 T7 = 5，所以VSPW = 5 - 1 = 4;
	 */
	lcd_regs->lcdcon3 = (16 << 19) | (239 << 8) | (10 << 0);
	lcd_regs->lcdcon4 = (4 << 0);

	/* 信号的极性
	 * bit[11]: 1 = 565 format
	 * bit[10]: 0 = The video data is fetched at VCLK falling edge
	 * bit[9] : 1 = Inverted, HSYNC信号要翻转，即低电平有效
	 * bit[8] : 1 = Inverted, VSYNC信号要翻转
	 * bit[6] : 0 = Normal
	 * bit[1] : 0 = BSWP
	 * bit[0] : 1 = HWSWP 2440手册P413
	 */
	lcd_regs->lcdcon5 = (1 << 11) | (1 << 9) | (1 << 8) | (1 << 0);
	
	/* 3.3 分配显存(framebuffer)，并把地址告诉LCD控制器 */
	s3c_lcd->screen_base = dma_alloc_writecombine(NULL, s3c_lcd->fix.smem_len, &s3c_lcd->fix.smem_start, GFP_KERNEL);
	
	lcd_regs->lcdsaddr1  = (s3c_lcd->fix.smem_start >> 1) & ~(3<<30);
	lcd_regs->lcdsaddr2  = ((s3c_lcd->fix.smem_start + s3c_lcd->fix.smem_len) >> 1) & 0x1fffff;
	lcd_regs->lcdsaddr3  = (LCD_SCR_XSIZE * 16/16);  /* 一行的长度(单位: 2字节) */	
	
	//s3c_lcd->fix.smem_start = xxx;  /* 显存的物理地址 */
	/* 启动LCD */
	lcd_regs->lcdcon1 |= (1 << 0);   /* 使能LCD控制器 */
	lcd_regs->lcdcon5 |= (1 << 3);   /* 使能LCD本身 */
	*gpbdat |= 1;				  /* 输出高电平，使能背光灯 */
	
	
	/* 4.注册 */
	register_framebuffer(s3c_lcd);
	
	return 0;
}

static void lcd_exit(void)
{
	unregister_framebuffer(s3c_lcd);

	lcd_regs->lcdcon1 &=~ (1 << 0);		/* 关闭LCD本身 */
	*gpbdat &=~ 1;
	dma_free_writecombine(NULL, s3c_lcd->fix.smem_len, s3c_lcd->screen_base, s3c_lcd->fix.smem_start);
	iounmap(lcd_regs);
	iounmap(gpbcon);
	iounmap(gpccon);
	iounmap(gpdcon);
	iounmap(gpgcon);

	framebuffer_release(s3c_lcd);
}

module_init(lcd_init);
module_exit(lcd_exit);


MODULE_LICENSE("GPL");
