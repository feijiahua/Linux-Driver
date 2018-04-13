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

	/* ��red,green,blue��ԭɫ�����val */
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
	/* ����һ��fb_info */
	s3c_lcd = framebuffer_alloc(0, NULL);
	/* 2.���� */
	/* 2.1 ���ù̶��Ĳ��� */
	strcpy(s3c_lcd->fix.id, "mylcd");
	s3c_lcd->fix.smem_len = LCD_SCR_XSIZE * LCD_SCR_YSIZE * 16/8;	//16 = 5 + 6 + 5, R:5λ��G:6λ��B:5λ smem_len��ʾ�Դ泤�ȣ���bitλΪ��λ
	s3c_lcd->fix.type = FB_TYPE_PACKED_PIXELS;//����
	s3c_lcd->fix.visual = FB_VISUAL_TRUECOLOR;//��������:���ɫ
	s3c_lcd->fix.line_length = LCD_SCR_XSIZE * 2;//һ����240�����أ�һ������16λ��Ҳ����2���ֽ�
		
	/* 2.2 ���ÿɱ�Ĳ��� */
	s3c_lcd->var.xres           = LCD_SCR_XSIZE;
	s3c_lcd->var.yres           = LCD_SCR_YSIZE;
	s3c_lcd->var.xres_virtual   = LCD_SCR_XSIZE;
	s3c_lcd->var.yres_virtual   = LCD_SCR_YSIZE;
	s3c_lcd->var.bits_per_pixel = 16;

	/* RGB:565,����R,G,B�����������ֽ��д�ŵ�λ�á����ȵ� */
	s3c_lcd->var.red.offset		= 11;
	s3c_lcd->var.red.length		= 5;

	s3c_lcd->var.green.offset	= 5;
	s3c_lcd->var.green.length	= 6;

	s3c_lcd->var.blue.offset	= 0;
	s3c_lcd->var.blue.length	= 5;

	s3c_lcd->var.activate		= FB_ACTIVATE_NOW;
	
	
	/* 2.3 ���ò������� */
	s3c_lcd->fbops= &s3c_lcdfb_ops;
	
	/* 2.4 �������� */
	s3c_lcd->pseudo_palette = pseudo_palette;
	//s3c_lcd->screen_base  = ;  /* �Դ�������ַ */ 
	s3c_lcd->screen_size   = LCD_SCR_XSIZE * LCD_SCR_YSIZE * 16/8;

	/* 3. Ӳ����صĲ��� */
	/* 3.1 ����GPIO����LCD */
	gpbcon = ioremap(0x56000010, 8);
	gpbdat = gpbcon + 1;
	gpccon = ioremap(0x56000020, 4);
	gpdcon = ioremap(0x56000030, 4);
	gpgcon = ioremap(0x56000060, 4);

	*gpccon  = 0xaaaaaaaa;   // GPIO�ܽ�����VD[7:0],LCDVF[2:0],VM,VFRAME,VLINE,VCLK,LEND 
	*gpdcon  = 0xaaaaaaaa;   // GPIO�ܽ�����VD[23:8]
	*gpbcon &=~ (3);
	*gpbcon |= 1;
	*gpbdat &= ~1;     /* ����͵�ƽ */

	*gpgcon |= (3<<8);	/* GPG4����LCD_PWREN */
	
	/* 3.2 ����LCD�ֲ�����LCD������������VCLK��Ƶ�ʵ� */
	lcd_regs = ioremap(0x4d000000, sizeof(struct lcd_regs));

	/* bit[17:8]: VCLK = HCLK / [(CLKVAL + 1) * 2], lcd�ֲ�P14;
	 * 			  10MHz(100ns) = 100MHz / [(CLKVAL + 1) * 2];
	 *			  CLKVAL = 4;
	 * bit[6:5] : 0b11, TFT LCD
	 * bit[4:1] : 0b1100, 16 bpp for TFT
	 * bit[0]   : 0 = Disable the video output and the LCD control signal.
	 */
	lcd_regs->lcdcon1 = (4 << 8) | (3 << 5) | (0x0c << 1);

	/* ��ֱ����ʱ����� 
	 * bit[31:24]: VBPD, VSYNC֮���ٹ��೤ʱ����ܷ�����һ������
	 * 			   LCD�ֲ� T0 - T2 - T1 = 4;
	 *             VBPD = 3;
	 * bit[23:14]: һ֡�����ж����У�320�У�����LINEVAL = 320 - 1 = 319;
	 * bit[13:6] : VFPD���������һ������֮���ٹ�����ʱ�䷢��VSYNC�ź�
	 * 			   LCD�ֲ� T2 - TY5 = 322 - 320 = 2������VFPD = 2 - 1 = 1;
	 * bit[5:0]  : VSPW, VSYNC�źŵ�������
	 *			   LCD�ֲ� T1 = 1������VSPW = 1 - 1 = 0;
	 */
	lcd_regs->lcdcon2 = (3 << 24) | (319 << 14); (1 << 6) | (0 << 0);

	/* ˮƽ����ʱ�����  
	 * bit[25:19]: HBPD, HSYNC֮���ٹ��೤ʱ����ܷ�����һ�����ص�����
	 * 			   LCD�ֲ� T6 - T7 - T8 = 17;
	 *             HBPD = 16;
	 * bit[18:8]: һ���ж��ٸ����أ�240�У�����HOZAL = 240 - 1 = 239;
	 * bit[7:0] : HFPD������һ�������һ������֮���ٹ�����ʱ�䷢��HSYNC�ź�
	 * 			   LCD�ֲ� T8 - TY11 = 251 - 240 = 11������VFPD = 11 - 1 = 10;
	 * LCDCON4
	 * bit[7:0]  : HSPW, HSYNC�źŵ�������
	 *			   LCD�ֲ� T7 = 5������VSPW = 5 - 1 = 4;
	 */
	lcd_regs->lcdcon3 = (16 << 19) | (239 << 8) | (10 << 0);
	lcd_regs->lcdcon4 = (4 << 0);

	/* �źŵļ���
	 * bit[11]: 1 = 565 format
	 * bit[10]: 0 = The video data is fetched at VCLK falling edge
	 * bit[9] : 1 = Inverted, HSYNC�ź�Ҫ��ת�����͵�ƽ��Ч
	 * bit[8] : 1 = Inverted, VSYNC�ź�Ҫ��ת
	 * bit[6] : 0 = Normal
	 * bit[1] : 0 = BSWP
	 * bit[0] : 1 = HWSWP 2440�ֲ�P413
	 */
	lcd_regs->lcdcon5 = (1 << 11) | (1 << 9) | (1 << 8) | (1 << 0);
	
	/* 3.3 �����Դ�(framebuffer)�����ѵ�ַ����LCD������ */
	s3c_lcd->screen_base = dma_alloc_writecombine(NULL, s3c_lcd->fix.smem_len, &s3c_lcd->fix.smem_start, GFP_KERNEL);
	
	lcd_regs->lcdsaddr1  = (s3c_lcd->fix.smem_start >> 1) & ~(3<<30);
	lcd_regs->lcdsaddr2  = ((s3c_lcd->fix.smem_start + s3c_lcd->fix.smem_len) >> 1) & 0x1fffff;
	lcd_regs->lcdsaddr3  = (LCD_SCR_XSIZE * 16/16);  /* һ�еĳ���(��λ: 2�ֽ�) */	
	
	//s3c_lcd->fix.smem_start = xxx;  /* �Դ�������ַ */
	/* ����LCD */
	lcd_regs->lcdcon1 |= (1 << 0);   /* ʹ��LCD������ */
	lcd_regs->lcdcon5 |= (1 << 3);   /* ʹ��LCD���� */
	*gpbdat |= 1;				  /* ����ߵ�ƽ��ʹ�ܱ���� */
	
	
	/* 4.ע�� */
	register_framebuffer(s3c_lcd);
	
	return 0;
}

static void lcd_exit(void)
{
	unregister_framebuffer(s3c_lcd);

	lcd_regs->lcdcon1 &=~ (1 << 0);		/* �ر�LCD���� */
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
