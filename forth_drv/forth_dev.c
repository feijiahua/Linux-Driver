#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>
#include <linux/poll.h>

static struct class *thirddrv_class;
static struct class_device *thirddrv_class_dev;

static unsigned long gpio_va;

#define GPIO_OFT(x) ((x) - 0x56000000)
#define GPFCON  (*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000050)))
#define GPFDAT  (*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000054)))
#define GPGCON  (*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000060)))
#define GPGDAT  (*(volatile unsigned long *)(gpio_va + GPIO_OFT(0x56000064)))

#define GPF0	(1 << 0)
#define GPF2	(1 << 2)
#define GPG3	(1 << 3)
#define GPG11 	(1 << 11)

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);

static volatile int ev_press = 0;

struct pin_desc{
	unsigned int pin;
	unsigned int key_val;
};

static unsigned char key_val;/* 必要时需要加锁保护 */

struct pin_desc pins_desc[4] = {
	{GPF0, 0x01},
	{GPF2, 0x02},
	{GPG3, 0x03},
	{GPG11, 0x04},
};

static irqreturn_t buttons_irq(int irq, void *dev_id)
{
	struct pin_desc *pindesc = (struct pin_desc *)dev_id;
	unsigned int pinval;

	if (pindesc->pin < 0x05)
		pinval = GPFDAT & pindesc->pin;
	else
		pinval = GPGDAT & pindesc->pin;
	/* 按键松开了 */
	if (pinval)
	{
		/* 加锁，不能加带阻塞的锁 */
		key_val = 0x80 | pindesc->key_val;
		/* 解锁 */
	}
	/* 按键按下 */
	else
	{
		/* 加锁，不能加带阻塞的锁 */
		key_val = pindesc->key_val;
		/* 解锁 */
	}

	ev_press = 1; /* 表示有按键按下了 */
	wake_up_interruptible(&button_waitq);	/* 唤醒休眠进程 */

	return IRQ_RETVAL(IRQ_HANDLED);
}

static int forth_drv_open(struct inode *inode, struct file *file)
{
	/* 引脚配置位中断模式 */
	GPFCON = ((2 << 0) | (2 << 4));
	GPGCON = ((2 << 6) | (2 << 22));

	request_irq(IRQ_EINT0, buttons_irq, IRQT_BOTHEDGE, "S2", &pins_desc[0]);
	request_irq(IRQ_EINT2, buttons_irq, IRQT_BOTHEDGE, "S3", &pins_desc[1]);
	request_irq(IRQ_EINT11, buttons_irq, IRQT_BOTHEDGE, "S4", &pins_desc[2]);
	request_irq(IRQ_EINT19, buttons_irq, IRQT_BOTHEDGE, "S5", &pins_desc[3]);

	return 0;
}

ssize_t forth_drv_read(struct file *file, char __user *buff, size_t size, loff_t *ppos)
{
	if (1 != size)
		return -EINVAL;

	/* 如果ev_press为0，即还没有按键按下，则休眠 */
	wait_event_interruptible(button_waitq, ev_press);

	/* 此时有按键按下 */
	/* 加锁，可以带阻塞 */
	copy_to_user(buff, (const void *)&key_val, 1);
	/* 解锁 */
	ev_press = 0;

	return 0;
}

int forth_drv_close(struct inode *inode, struct file *file)
{
	free_irq(IRQ_EINT0, &pins_desc[0]);
	free_irq(IRQ_EINT2, &pins_desc[1]);
	free_irq(IRQ_EINT3, &pins_desc[2]);
	free_irq(IRQ_EINT11, &pins_desc[3]);

	return 0;
}

static unsigned int forth_drv_poll(struct file *file, poll_table *wait)
{
	unsigned int mask = 0;
	poll_wait(file, &button_waitq, wait);

	if (ev_press)
		mask |= POLLIN | POLLRDNORM;

	return mask;
}

static struct file_operations forth_drv_fops = {
	.owner		=	THIS_MODULE,
	.open 		=	forth_drv_open,
	.read 		=	forth_drv_read,
	.release 	=	forth_drv_close,
	.poll 		=	forth_drv_poll,
};

int major;

static int forth_drv_init(void)
{
	major = register_chrdev(0, "forth_drv", &forth_drv_fops);

	thirddrv_class = class_create(THIS_MODULE, "forth_drv");
	thirddrv_class_dev = class_device_create(thirddrv_class, NULL, MKDEV(major, 0), NULL, "buttons");

	gpio_va = ioremap(0x56000000, 0x100000);

	return 0;
}

static void forth_drv_exit(void)
{
	unregister_chrdev(major, "forth_drv");

	class_device_unregister(thirddrv_class_dev);
	class_destroy(thirddrv_class);

	iounmap(gpio_va);

	return 0;
}

module_init(forth_drv_init);
module_exit(forth_drv_exit);

MODULE_LICENSE("GPL");