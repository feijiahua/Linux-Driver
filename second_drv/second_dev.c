/*
* 查询方式检测按键
* 按键接口：GPF0(ENIT0)
* 			GPF2(ENIT2)
* 			GPG3(ENIT11)
* 			GPG11(ENIT19)
*/

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

#define DEVICE_NAME	"second_drv"
#define DEVICE_MAJOR	232

static struct class *seconddrv_class;
static struct class_device *seconddrv_class_dev;

static unsigned long gpio_va;

#define GPIO_OFT(x)	((x) - 0x56000000)
#define GPFCON	(*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000050)))
#define GPFDAT	(*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000054)))
#define GPGCON	(*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000060)))
#define GPGDAT	(*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000064)))

static int second_drv_open(struct inode *inode, struct file *file)
{
	GPFCON &=~ ((3 << 0) | (3 << 4));
	GPGCON &=~ ((3 << 6) | (3 << 22));

	return 0;
}

static int second_drv_read(struct file *filp, char __user *buff, size_t count, loff_t *offp)
{
	unsigned char key_val[4];

	if (sizeof(key_val) != count)
	{
		printk("error\n");
		return -EINVAL;
	}

	key_val[0] = (GPFDAT & (1 << 0)) ? 1 : 0;
	key_val[1] = (GPFDAT & (1 << 2)) ? 1 : 0;
	key_val[2] = (GPGDAT & (1 << 3)) ? 1 : 0;
	key_val[3] = (GPGDAT & (1 << 11)) ? 1 : 0;
	copy_to_user(buff, (void *)key_val, sizeof(key_val));

	return sizeof(key_val);
}

static struct file_operations second_drv_fops = 
{
	.owner	= 	THIS_MODULE,
	.open 	= 	second_drv_open,
	.read 	=	second_drv_read,
};

static int second_drv_init(void)
{
	register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &second_drv_fops);

	seconddrv_class = class_create(THIS_MODULE, "seconddrv");
	seconddrv_class_dev = class_device_create(seconddrv_class, NULL, MKDEV(DEVICE_MAJOR, 0), NULL, "buttons");

	gpio_va = ioremap(0x56000000, 0x100000);

	return 0;
}

static void second_drv_exit(void)
{
	unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);

	class_device_unregister(seconddrv_class_dev);
	class_destroy(seconddrv_class);

	iounmap(gpio_va);

	return;
}

module_init(second_drv_init);
module_exit(second_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bigfeifei");
