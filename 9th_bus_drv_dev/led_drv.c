/* 分配/设置/注册一个platform_driver */
#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/io.h>

int pin[3];
int major;
struct class *led_class;
struct class_device *led_class_device[3];
static volatile unsigned long *gpio_con;
static volatile unsigned long *gpio_dat;

static int led_open(struct inode *inode, struct file *file)
{
	int minor = MINOR(inode->i_rdev);

	*gpio_con &=~ (0x3 << (pin[minor]*2));
	*gpio_con |=  (0x1 << (pin[minor]*2));
	/* 设置输出引脚 */

	return 0;
}

static ssize_t led_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	int minor = MINOR(file->f_dentry->d_inode->i_rdev);
	char val;

	copy_from_user(&val, buf, count);

	if (0 == val)
	{
		*gpio_dat &=~ (1 << pin[minor]);
	}
	else
	{
		*gpio_dat |= (1 << pin[minor]);
	}

	return 0;
}

struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.open = led_open,
	.write = led_write,
};

static int led_probe(struct platform_device *pdev)
{
	int i;
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);	/* 0表示IOSOURCE_MEM类型的第0个资源 */
	gpio_con = ioremap(res->start, res->end - res->start + 1);
	gpio_dat = gpio_con + 1;

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	pin[0] = res->start;
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 1);
	pin[1] = res->start;
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 2);
	pin[2] = res->start;

	/* 注册字符设备 */
	major = register_chrdev(0, "myled", &led_fops);

	led_class = class_create(THIS_MODULE, "myled");
	for (i = 0; i < 3; i++)
	{
		led_class_device[i] = class_device_create(led_class, NULL, MKDEV(major, i), NULL, "led%d", i);
	}

	printk("led_probe, find device\n");


	return 0;
}

static int led_remove(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		class_device_unregister(led_class_device[i]);
	}
	
	class_destroy(led_class);

	unregister_chrdev(major, "myled");

	iounmap(gpio_con);

	printk("remove device\n");

	return 0;
}

static struct platform_driver led_drv = {
	.probe = led_probe,
	.remove = led_remove,
	.driver = {
		.name = "myled",
	},
};

static int led_drv_init(void)
{
	platform_driver_register(&led_drv);
	return 0;
}

static void led_drv_exit(void)
{
	platform_driver_unregister(&led_drv);
}

module_init(led_drv_init);
module_exit(led_drv_exit);

MODULE_LICENSE("GPL");