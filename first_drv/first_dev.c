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

#define DEVICE_NAME "leds"
#define LED_MAJOR 231

static struct class *firstdrv_class;
static struct class_device *firstdrv_class_dev[3];

/* bit0 = D10, 0:亮，1:灭
 * bit1 = D11, 0:亮，1:灭
 * bit2 = D12, 0:亮，1:灭
 */
static char leds_status = 0x0;
static DECLARE_MUTEX(leds_lock); /* 互斥信号量 */

static unsigned long gpio_va;

#define GPIO_OFT(x) ((x) - 0x56000000)
#define GPFCON	(*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000050)))
#define GPFDAT	(*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000054)))

#define GPF4	(1 << (4 * 2))
#define GPF5	(1 << (5 * 2))
#define GPF6	(1 << (6 * 2))


static int first_drv_open(struct inode *inode, struct file *file)
{
	/*
	printk("first_drv_open\n");
	return 0;
	*/
	int minor = MINOR(inode->i_rdev); /* 获取次设备号 */

	switch(minor)
	{
		case 0:
		{
			GPFCON |= GPF4;
			GPFDAT &=~ (1 << 4);

			down(&leds_lock);
			leds_status &=~ (1 << 0);
			up(&leds_lock);
			break;
		}
		case 1:
		{
			GPFCON |= GPF5;
			GPFDAT &=~ (1 << 5);

			down(&leds_lock);
			leds_status &=~ (1 << 1);
			up(&leds_lock);
			break;
		}
		case 2:
		{
			GPFCON |= GPF6;
			GPFDAT &=~ (1 << 6);

			down(&leds_lock);
			leds_status &=~ (1 << 2);
			up(&leds_lock);
			break;
		}
	}
	return 0;
}

static int first_drv_read(struct file *filp, char __user *buff, size_t count, loff_t *offp)
{
	int minor = MINOR(filp->f_dentry->d_inode->i_rdev);
	char val;

	down(&leds_lock);
	val = leds_status;
	up(&leds_lock);

	copy_to_user(buff, (const void *)&val, 1);

	return 0;
}

static ssize_t first_drv_write(struct file *file, const char __user *buff, size_t count, loff_t *ppos)
{
	int minor = MINOR(file->f_dentry->d_inode->i_rdev);
	char val;

	copy_from_user(&val, buff, 1);

	if (0 == val)
	{
		down(&leds_lock);
		leds_status |= (1 << minor);
		up(&leds_lock);
		GPFDAT &=~ (1 << (4 + minor));
	}
	else
	{
		down(&leds_lock);
		leds_status &=~ (1 << minor);
		up(&leds_lock);
		GPFDAT |= (1 << (4 + minor));
	}

	return 0;
}

static struct file_operations first_drv_fops = {
	.owner = THIS_MODULE,
	.open = first_drv_open,
	.read = first_drv_read,
	.write = first_drv_write,
};

static int __init first_drv_init(void)
{
	int ret;
	int minor = 0;

	gpio_va = ioremap(0x56000000, 0x100000);
	if (!gpio_va)
	{
		return -EIO; 
	}

	ret = register_chrdev(LED_MAJOR, DEVICE_NAME, &first_drv_fops);
	if (ret < 0)
	{
		printk(DEVICE_NAME "can't register major number\n");
		return ret;
	}

	firstdrv_class = class_create(THIS_MODULE, "leds");
	if (IS_ERR(firstdrv_class))
		return PTR_ERR(firstdrv_class);
	for (minor = 0; minor < 3; minor++)
	{
		firstdrv_class_dev[minor] = class_device_create(firstdrv_class, NULL, MKDEV(LED_MAJOR, minor), NULL, "led%d", minor);
		if (IS_ERR(firstdrv_class_dev[minor]))
			return PTR_ERR(firstdrv_class_dev);
	}
	printk(DEVICE_NAME " initialized succeed\n");
	return 0;
}

static void __exit first_drv_exit(void)
{
	int minor;

	unregister_chrdev(LED_MAJOR, DEVICE_NAME);

	for (minor = 0; minor < 3; minor++)
	{
		class_device_unregister(firstdrv_class_dev[minor]);
	}

	class_destroy(firstdrv_class);
	iounmap(gpio_va);

	printk(DEVICE_NAME " remove success\n");

	return;
}

module_init(first_drv_init);
module_exit(first_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bigfeifei");