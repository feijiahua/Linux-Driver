#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/hardware.h>

#define MAJOR 231

static struct class *firstdrv_class;
static struct class_device *firstdrv_class_dev;

volatile unsigned long *gpfcon = NULL;
volatile unsigned long *gpfdat = NULL;

static int first_drv_open(struct inode *inode, struct file *file)
{
	//printk("first_drv_open\n");
	/* ÅäÖÃGPF4, 5, 6ÎªÊä³ö */
	*gpfcon &=~ ((0x3<<(4*2)) | (0x3<<(5*2)) | (0x3<<(6*2)));
	*gpfcon |= ((0x1<<(4*2)) | (0x1<<(5*2)) | (0x1<<(6*2)));

	return 0;
}

static int first_drv_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	int val;
	
	//printk("first_drv_write\n");
	/* ´ÓÓÃ»§¿Õ¼ä½«count³¤¶ÈµÄbuf»º´æÊý¾Ý¿½±´µ½ÄÚºË¿Õ¼äval±äÁ¿ */
	copy_from_user(&val, buf, count);//copy_to_user();¿½±´µ½ÓÃ»§¿Õ¼ä
	
	if (1 == val)
	{
		//µãµÆ
		*gpfdat &= ~((1 << 4) | (1 << 5) | (1 << 6));
	}
	else
	{
		//ÃðµÆ
		*gpfdat |= (1 << 4) | (1 << 5) | (1 << 6);
	}
	
	return 0;
}

static struct file_operations first_drv_fops = {
	.owner = THIS_MODULE,
	.open = first_drv_open,
	.write = first_drv_write,
};
/* ï¿½ï¿½×°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ */

static int __init first_drv_init(void)
{
	int major;

	//printk("first_drv_init\n");
	register_chrdev(MAJOR, "first_drv", &first_drv_fops); /* ï¿½Ô¶ï¿½ï¿½ï¿½È¡ï¿½ï¿½ï¿½è±¸ï¿½ï¿½ */

	/* ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½ */
	firstdrv_class = class_create(THIS_MODULE, "firstdrv");
	if (IS_ERR(firstdrv_class))
		return PTR_ERR(firstdrv_class);

	/* ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½è±¸ */
	firstdrv_class_dev = class_device_create(firstdrv_class, NULL, MKDEV(MAJOR, 0), NULL, "xyz");  /* /dev/xyz,ï¿½è±¸ï¿½Úµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Îªxyz */
	if (unlikely(IS_ERR(firstdrv_class_dev)))
		return PTR_ERR(firstdrv_class_dev);
	
	/* µØÖ·Ó³Éä£¬gpfcon¼Ä´æÆ÷µÄÐéÄâµØÖ·Ê±0X56000050 */
	gpfcon = (volatile unsigned long *)ioremap(0x56000050, 16);
	gpfdat = gpfcon + 1;
	
	return 0;
}

/* Ð¶ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ */
static void __exit first_drv_exit(void)
{
	//printk("first_drv_exit\n");
	unregister_chrdev(MAJOR, "first_drv"); //Ð¶ï¿½ï¿½

	/* É¾ï¿½ï¿½ï¿½è±¸ï¿½Úµï¿½ */
	class_device_unregister(firstdrv_class_dev);
	class_destroy(firstdrv_class);

	/* È¡ÏûµØÖ·Ó³Éä */
	iounmap(gpfcon);
	
	return ;
}

module_init(first_drv_init);
module_exit(first_drv_exit);

MODULE_LICENSE("GPL");
