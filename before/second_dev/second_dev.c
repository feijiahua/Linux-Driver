#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

#define DEVICE_NAME "second_drv"
#define DEVICE_MAJOR 232

static struct class *seconddrv_class;
static struct class_device *seconddrv_class_dev;

static unsigned long gpio_va;

#define GPIO_OFT(x) ((x) - 0x56000000)
#define GPFCON  (*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000050)))
#define GPFDAT  (*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000054)))
#define GPGCON  (*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000060)))
#define GPGDAT  (*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000064)))

static int second_drv_open(struct inode *inode, struct file *file)
{
	/* 配置GPF2为输入 */
	GPFCON &=~ ((0x3 << (3 * 2)) | (0x3 << (11 * 2)));
	GPGCON &=~ ((0x3 << (3 * 2)) | (0x3 << (11 * 2)));
	return 0;
}

static int second_drv_read(struct file *filp, char __user *buff, 
                                         size_t count, loff_t *offp)
{
	unsigned char key_vals[4];

	if (count != sizeof(key_vals))
		return -EINVAL;

	/* 读GPF0， 2 */
	key_vals[0] = (GPFDAT & (1 << 0)) ? 1 : 0;
	key_vals[1] = (GPFDAT & (1 << 2)) ? 1 : 0;

	/* 读GPG3， 11 */
	key_vals[2] = (GPGDAT & (1 << 3)) ? 1 : 0;
	key_vals[3] = (GPGDAT & (1 << 11)) ? 1 : 0;

	copy_to_user(buff, (const void *)key_vals, sizeof(key_vals));

	return sizeof(key_vals);
}

static struct file_operations second_drv_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   second_drv_open,     
	.read	=	second_drv_read,	   
	//.write	=	second_drv_write,	   
};

static int sencond_drv_init(void)
{
	/* 注册file_operations结构体 */
	register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &second_drv_fops);
	/* 创建类和设备 */
	seconddrv_class = class_create(THIS_MODULE, "seconddrv");
	seconddrv_class_dev = class_device_create(seconddrv_class, NULL, MKDEV(DEVICE_MAJOR, 0), NULL, "buttons");  /* /dev/buttons */
	/* 地址映射 */
	gpio_va = ioremap(0x56000000, 0x100000);

	return 0; 
}

static void second_drv_exit(void)
{
	unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
	/* 卸载类和设备 */
	class_device_unregister(seconddrv_class_dev);
	class_destroy(seconddrv_class);
	/* 消除地址映射 */
	iounmap(gpio_va);

	return ;
}

module_init(sencond_drv_init);
module_exit(second_drv_exit);

MODULE_LICENSE("GPL");