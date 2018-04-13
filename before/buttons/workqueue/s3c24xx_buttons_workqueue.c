/* 自动加载设备节点 */
/* 使用工作队列 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>
#include <asm/io.h>

#define DEVICE_NAME		"buttons"
#define BUTTON_MAJOR 	232

static struct class *buttons_class;
static struct class_device	*buttons_class_devs[4];

volatile unsigned long *gpfcon;
volatile unsigned long *gpfdat;

volatile unsigned long *gpgcon;
volatile unsigned long *gpgdat;

struct button_irq_desc{
	int irq;					/* 中断号 */
	unsigned long flags;		/* 中断标志 */
	char *name;					/* 中断名称 */
};

static struct button_irq_desc button_irqs[] = {
    {IRQ_EINT19, IRQF_TRIGGER_FALLING, "KEY1"}, /* K1 */
    {IRQ_EINT11, IRQF_TRIGGER_FALLING, "KEY2"}, /* K2 */
    {IRQ_EINT2,  IRQF_TRIGGER_FALLING, "KEY3"}, /* K3 */
    {IRQ_EINT0,  IRQF_TRIGGER_FALLING, "KEY4"}, /* K4 */
};

static volatile int press_cnt [] = {0, 0, 0, 0};

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);

static volatile int ev_press = 0;

struct work_struct my_work;

void work_handler(struct work_struct *data)
{
	printk("work_handler is running\n");
	return ;
}

/* 由于各个按键都在各自的中断线上，所以不需要判断是哪个按键按下 */
static irqreturn_t buttons_interrupt(int irq, void *dev_id)
{
	volatile int *press_cnt = (volatile int *)dev_id;

	schedule_work(&my_work);

	*press_cnt = *press_cnt + 1;
	ev_press = 1;
	wake_up_interruptible(&button_waitq);    /* 唤醒休眠的进程 */

	return IRQ_RETVAL(IRQ_HANDLED);
}

/* 设置io输出，注册中断处理函数 */
/* 需要改进：根据次设备号开启设备 */
static int s3c24xx_buttons_open(struct inode *inode, struct file *file)
{
	int i;
	int minor = MINOR(inode->i_rdev); /* 获取次设备号 */
	int err;

	/* 初始化引脚 */
	/* 配置GPF0,2为输入引脚 */
	*gpfcon &= ~((0x3<<(0*2)) | (0x3<<(2*2)));

	/* 配置GPG3,11为输入引脚 */
	*gpgcon &= ~((0x3<<(3*2)) | (0x3<<(11*2)));
	/* 注册中断 */
	err = request_irq(button_irqs[minor].irq, buttons_interrupt, button_irqs[minor].flags, 
					button_irqs[minor].name, (void *)&press_cnt[minor]);
	if (err)
	{
		free_irq(button_irqs[minor].irq, (void *)&press_cnt[minor]);
		return -1;
	}

	INIT_WORK(&my_work, work_handler);

	return 0;
}

/* 卸载中断处理函数 */
/* 需要改进：根据次设备号关闭设备 */
static int s3c24xx_buttons_close(struct inode *inode, struct file *file)
{
	int minor = MINOR(inode->i_rdev); /* 获取次设备号 */

	free_irq(button_irqs[minor].irq, (void *)&press_cnt[minor]);

	return 0;
}

/* 读键值 */
/* 需要改进：根据次设备号读取设备 */
static int s3c24xx_buttons_read(struct file *filp, char __user *buff, 
                                         size_t count, loff_t *offp)
{
	int minor = MINOR(filp->f_dentry->d_inode->i_rdev);
	unsigned long err;
	/* 如果ev_press=0，休眠 */
	wait_event_interruptible(button_waitq, ev_press);
	/* 运行到这说明ev_press肯定为1，将他清零 */
	ev_press = 0;

	/* 将案件状态复制给用户，并清零 */
	/* 需要改进：根据从设备号拷贝press_cnt中的对应成员的值 */
	err = copy_to_user(buff, (const void *)&press_cnt[minor], min(sizeof(int), count));

	//press_cnt[minor] = 0;
	//memset((void *)press_cnt, 0, sizeof(press_cnt));


	return err ? -EFAULT : 0;
}

static struct file_operations s3c24xx_buttons_fops = {
    .owner   =   THIS_MODULE,    /* 这是一个宏，指向编译模块时自动创建的__this_module变量 */
    .open    =   s3c24xx_buttons_open,
    .release =   s3c24xx_buttons_close, 
    .read    =   s3c24xx_buttons_read,
};

static int __init s3c24xx_buttons_init(void)
{

	int minor;
	int ret;

	/* 在系统中注册s3c24xx_buttons_fops结构 */
	ret = register_chrdev(BUTTON_MAJOR, DEVICE_NAME, &s3c24xx_buttons_fops);
	if (ret < 0)
	{
		printk(DEVICE_NAME "can't register major number\n");
		return ret;
	}
	/* 自动加载设备节点 */
	buttons_class = class_create(THIS_MODULE, "buttons");
	//buttons_class_devs = class_device_create(buttons_class, NULL, MKDEV(BUTTON_MAJOR, 0), NULL, "buttons"); /* /dev/buttons */

	for (minor = 0; minor < 4; minor++)
	{
		buttons_class_devs[minor] = class_device_create(buttons_class, NULL, MKDEV(BUTTON_MAJOR, minor), NULL, "button%d", minor);
		if (unlikely(IS_ERR(buttons_class_devs[minor])))
			return PTR_ERR(buttons_class_devs[minor]);
	} 

	printk(DEVICE_NAME "initialized\n");

	gpfcon = (volatile unsigned long *)ioremap(0x56000050, 16);
	gpfdat = gpfcon + 1;

	gpgcon = (volatile unsigned long *)ioremap(0x56000060, 16);
	gpgdat = gpgcon + 1;

	return 0;
}
/* 需要改进：删除类及设备 */
static void s3c24xx_buttons_exit(void)
{
	int minor;
	/* 卸载驱动程序 */
	unregister_chrdev(BUTTON_MAJOR, DEVICE_NAME);

	for (minor = 0; minor < 4; minor++)
	{
		class_device_unregister(buttons_class_devs[minor]);
	}
	class_destroy(buttons_class);
	iounmap(gpfcon);
	iounmap(gpgcon);

	return;
}

module_init(s3c24xx_buttons_init);
module_exit(s3c24xx_buttons_exit);

MODULE_LICENSE("GPL");
