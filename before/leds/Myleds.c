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

static struct class *leds_class;
static struct class_device *leds_class_devs[3];

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


static int s3c24xx_leds_open(struct inode *inode, struct file *file)
{
	int minor = MINOR(inode->i_rdev); /* 获取次设备号 */

	switch(minor)
	{
		case 0:
		{
			s3c2410_gpio_cfgpin(S3C2410_GPF4, S3C2410_GPF4_OUTP);
			s3c2410_gpio_setpin(S3C2410_GPF4, 0);

			down(&leds_lock);
			leds_status &=~ (1 << 0);
			up(&leds_lock);
			break;
		}
		case 1:
		{
			s3c2410_gpio_cfgpin(S3C2410_GPF5, S3C2410_GPF5_OUTP);
			s3c2410_gpio_setpin(S3C2410_GPF5, 0);

			down(&leds_lock);
			leds_status &=~ (1 << 1);
			up(&leds_lock);
			break;
		}
		case 2:
		{
			s3c2410_gpio_cfgpin(S3C2410_GPF6, S3C2410_GPF4_OUTP);
			s3c2410_gpio_setpin(S3C2410_GPF6, 0);

			down(&leds_lock);
			leds_status &=~ (1 << 2);
			up(&leds_lock);
			break;
		}
	}

	return 0;
}

static int s3c24xx_leds_read(struct file *filp, char __user *buff, 
                                         size_t count, loff_t *offp)
{
	int minor = MINOR(filp->f_dentry->d_inode->i_rdev);
	char val;

	switch(minor)
	{
		case 0:
		{
			down(&leds_lock);
			val = leds_status & 0x1;
			up(&leds_lock);
			copy_to_user(buff, (const void *)&val, 1);
			break;
		}
		case 1:
		{
			down(&leds_lock);
			val = leds_status & 0x2;
			up(&leds_lock);
			copy_to_user(buff, (const void *)&val, 1);
			break;
		}
		case 2:
		{
			down(&leds_lock);
			val = leds_status & 0x4;
			up(&leds_lock);
			copy_to_user(buff, (const void *)&val, 1);
			break;
		}
	}

	return 0;
}

static ssize_t s3c24xx_leds_write(struct file *file, const char __user *buff, size_t count, loff_t * ppos)
{
	int minor = MINOR(file->f_dentry->d_inode->i_rdev);
	char val;

	copy_from_user(&val, buff, 1);

	switch(minor)
	{
		case 0:
		{
			s3c2410_gpio_setpin(S3C2410_GPF4, val);

			if (0 == val)
			{
				down(&leds_lock);
				leds_status &=~ 0x1;
				up(&leds_lock);
			}
			else
			{
				down(&leds_lock);
				leds_status |= 0x1;
				up(&leds_lock);
			}
			break;
		}
		case 1:
		{
			s3c2410_gpio_setpin(S3C2410_GPF5, val);

			if (0 == val)
			{
				down(&leds_lock);
				leds_status &=~ 0x2;
				up(&leds_lock);
			}
			else
			{
				down(&leds_lock);
				leds_status |= 0x2;
				up(&leds_lock);
			}
			break;
		}
		case 2:
		{
			s3c2410_gpio_setpin(S3C2410_GPF6, val);

			if (0 == val)
			{
				down(&leds_lock);
				leds_status &=~ 0x4;
				up(&leds_lock);
			}
			else
			{
				down(&leds_lock);
				leds_status |= 0x4;
				up(&leds_lock);
			}
			break;
		}
	}

	return 0;
}

static struct file_operations s3c24xx_leds_fops = {
	.owner = THIS_MODULE,
	.open = s3c24xx_leds_open,
	.read = s3c24xx_leds_read,
	.write = s3c24xx_leds_write,
};

static int __init s3c24xx_leds_init(void)
{
	int ret;
	int minor = 0;

	gpio_va = ioremap(0x56000000, 0x100000);
	if (!gpio_va)
	{
		return -EIO;
	}

	ret = register_chrdev(LED_MAJOR, DEVICE_NAME, &s3c24xx_leds_fops);
	if (ret < 0)
	{
		printk(DEVICE_NAME "can't register major number\n");
		return ret;
	}

	leds_class = class_create(THIS_MODULE, "leds");
	if (IS_ERR(leds_class))
		return PTR_ERR(leds_class);

	leds_class_devs[0] = class_device_create(leds_class, NULL, MKDEV(LED_MAJOR, 0), NULL, "led0");

	for (minor = 1; minor < 3; minor++)
	{
		leds_class_devs[minor] = class_device_create(leds_class, NULL, MKDEV(LED_MAJOR, minor), NULL, "led%d", minor);
		if (IS_ERR(leds_class_devs[minor]))
			return PTR_ERR(leds_class_devs[minor]);
	}
	printk(DEVICE_NAME "initialized\n");
	return 0;
}

static void __exit s3c24xx_leds_exit(void)
{
	int minor;

	unregister_chrdev(LED_MAJOR, DEVICE_NAME);

	for (minor = 0; minor < 3; minor++)
	{
		class_device_unregister(leds_class_devs[minor]);
	}
	class_destroy(leds_class);
	iounmap(gpio_va);
	return;
}

module_init(s3c24xx_leds_init);
module_exit(s3c24xx_leds_exit);

MODULE_AUTHOR("bigfeifei");
MODULE_VERSION("0.1.0");
MODULE_LICENSE("GPL");