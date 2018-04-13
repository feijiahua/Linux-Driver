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


static struct class *seventhdrv_class;
static struct class_device	*seventhdrv_class_dev;

volatile unsigned long *gpfcon;
volatile unsigned long *gpfdat;

volatile unsigned long *gpgcon;
volatile unsigned long *gpgdat;


static DECLARE_WAIT_QUEUE_HEAD(button_waitq);

/* �ж��¼���־, �жϷ����������1��seventh_drv_read������0 */
static volatile int ev_press = 0;

static struct fasync_struct *button_async;

static struct timer_list buttons_timer;


struct pin_desc{
	unsigned int pin;
	unsigned int key_val;
};


/* ��ֵ: ����ʱ, 0x01, 0x02, 0x03, 0x04 */
/* ��ֵ: �ɿ�ʱ, 0x81, 0x82, 0x83, 0x84 */
static unsigned char key_val;

struct pin_desc pins_desc[4] = {
	{S3C2410_GPF0, 0x01},
	{S3C2410_GPF2, 0x02},
	{S3C2410_GPG3, 0x03},
	{S3C2410_GPG11, 0x04},
};

static struct pin_desc *irq_pd;


//static atomic_t canopen = ATOMIC_INIT(1);     //����ԭ�ӱ�������ʼ��Ϊ1

static DECLARE_MUTEX(button_lock);     //���廥����

/*
  * ȷ������ֵ
  */
static irqreturn_t buttons_irq(int irq, void *dev_id)
{
	irq_pd = (struct pin_desc *)dev_id;
	/* ���ó�ʱʱ��Ϊ10ms������ǰϵͳʱ��+10ms */
	mod_timer(&buttons_timer, jiffies + HZ/100); /* ϵͳʱ��ÿ��10ms����һ���жϣ�����jiffiesÿ��10ms+1��HZΪ100�� ��ʾһ���ӣ���ô10ms��ΪHZ/100 */
	
	return IRQ_RETVAL(IRQ_HANDLED);
}

static int seventh_drv_open(struct inode *inode, struct file *file)
{
#if 0	
	if (!atomic_dec_and_test(&canopen))
	{
		atomic_inc(&canopen);
		return -EBUSY;
	}
#endif		

	if (file->f_flags & O_NONBLOCK)
	{
		if (down_trylock(&button_lock))
			return -EBUSY;
	}
	else
	{
		/* ��ȡ�ź��� */
		down(&button_lock);
	}

	/* ����GPF0,2Ϊ�������� */
	/* ����GPG3,11Ϊ�������� */
	request_irq(IRQ_EINT0,  buttons_irq, IRQT_BOTHEDGE, "S2", &pins_desc[0]);
	request_irq(IRQ_EINT2,  buttons_irq, IRQT_BOTHEDGE, "S3", &pins_desc[1]);
	request_irq(IRQ_EINT11, buttons_irq, IRQT_BOTHEDGE, "S4", &pins_desc[2]);
	request_irq(IRQ_EINT19, buttons_irq, IRQT_BOTHEDGE, "S5", &pins_desc[3]);	

	return 0;
}

ssize_t seventh_drv_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	if (size != 1)
		return -EINVAL;

	if (file->f_flags & O_NONBLOCK)
	{
		if (!ev_press)
			return -EAGAIN;
	}
	else
	{
		/* ���û�а�������, ���� */
		wait_event_interruptible(button_waitq, ev_press);
	}

	/* ����а�������, ���ؼ�ֵ */
	copy_to_user(buf, &key_val, 1);
	ev_press = 0;
	
	return 1;
}


int seventh_drv_close(struct inode *inode, struct file *file)
{
	//atomic_inc(&canopen);
	free_irq(IRQ_EINT0, &pins_desc[0]);
	free_irq(IRQ_EINT2, &pins_desc[1]);
	free_irq(IRQ_EINT11, &pins_desc[2]);
	free_irq(IRQ_EINT19, &pins_desc[3]);
	up(&button_lock);
	return 0;
}

static unsigned seventh_drv_poll(struct file *file, poll_table *wait)
{
	unsigned int mask = 0;
	poll_wait(file, &button_waitq, wait); // ������������

	if (ev_press)
		mask |= POLLIN | POLLRDNORM;

	return mask;
}

static int seventh_drv_fasync (int fd, struct file *filp, int on)
{
	printk("driver: seventh_drv_fasync\n");
	return fasync_helper (fd, filp, on, &button_async);
}


static struct file_operations sencod_drv_fops = {
    .owner   =  THIS_MODULE,    /* ����һ���꣬�������ģ��ʱ�Զ�������__this_module���� */
    .open    =  seventh_drv_open,     
	.read	 =	seventh_drv_read,	   
	.release =  seventh_drv_close,
	.poll    =  seventh_drv_poll,
	.fasync	 =  seventh_drv_fasync,
};

static void button_timer_function(unsigned long data)
{
	struct pin_desc * pindesc = (struct pin_desc *)irq_pd;
	unsigned int pinval;
	
	if (NULL == pindesc)
		return;

	pinval = s3c2410_gpio_getpin(pindesc->pin);

	if (pinval)
	{
		/* �ɿ� */
		key_val = 0x80 | pindesc->key_val;
	}
	else
	{
		/* ���� */
		key_val = pindesc->key_val;
	}

    ev_press = 1;                  /* ��ʾ�жϷ����� */
    wake_up_interruptible(&button_waitq);   /* �������ߵĽ��� */
	
	kill_fasync (&button_async, SIGIO, POLL_IN);
}

int major;
static int seventh_drv_init(void)
{
	init_timer(&buttons_timer);
	//buttons_timer.data = (unsigned long)SCpnt; /* �ò�����function������������˴������ò��� */
	buttons_timer.function = (void (*)(unsigned long))button_timer_function;
	add_timer(&buttons_timer);

	major = register_chrdev(0, "seventh_drv", &sencod_drv_fops);

	seventhdrv_class = class_create(THIS_MODULE, "seventh_drv");

	seventhdrv_class_dev = class_device_create(seventhdrv_class, NULL, MKDEV(major, 0), NULL, "buttons"); /* /dev/buttons */

	gpfcon = (volatile unsigned long *)ioremap(0x56000050, 16);
	gpfdat = gpfcon + 1;

	gpgcon = (volatile unsigned long *)ioremap(0x56000060, 16);
	gpgdat = gpgcon + 1;

	return 0;
}

static void seventh_drv_exit(void)
{
	unregister_chrdev(major, "seventh_drv");
	class_device_unregister(seventhdrv_class_dev);
	class_destroy(seventhdrv_class);
	iounmap(gpfcon);
	iounmap(gpgcon);
	return 0;
}


module_init(seventh_drv_init);

module_exit(seventh_drv_exit);

MODULE_LICENSE("GPL");

