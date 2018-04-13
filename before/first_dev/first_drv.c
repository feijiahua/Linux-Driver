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
	/* ����GPF4, 5, 6Ϊ��� */
	*gpfcon &=~ ((0x3<<(4*2)) | (0x3<<(5*2)) | (0x3<<(6*2)));
	*gpfcon |= ((0x1<<(4*2)) | (0x1<<(5*2)) | (0x1<<(6*2)));

	return 0;
}

static int first_drv_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	int val;
	
	//printk("first_drv_write\n");
	/* ���û��ռ佫count���ȵ�buf�������ݿ������ں˿ռ�val���� */
	copy_from_user(&val, buf, count);//copy_to_user();�������û��ռ�
	
	if (1 == val)
	{
		//���
		*gpfdat &= ~((1 << 4) | (1 << 5) | (1 << 6));
	}
	else
	{
		//���
		*gpfdat |= (1 << 4) | (1 << 5) | (1 << 6);
	}
	
	return 0;
}

static struct file_operations first_drv_fops = {
	.owner = THIS_MODULE,
	.open = first_drv_open,
	.write = first_drv_write,
};
/* ��װ�������� */

static int __init first_drv_init(void)
{
	int major;

	//printk("first_drv_init\n");
	register_chrdev(MAJOR, "first_drv", &first_drv_fops); /* �Զ���ȡ���豸�� */

	/* ����һ���� */
	firstdrv_class = class_create(THIS_MODULE, "firstdrv");
	if (IS_ERR(firstdrv_class))
		return PTR_ERR(firstdrv_class);

	/* ����һ���豸 */
	firstdrv_class_dev = class_device_create(firstdrv_class, NULL, MKDEV(MAJOR, 0), NULL, "xyz");  /* /dev/xyz,�豸�ڵ�������Ϊxyz */
	if (unlikely(IS_ERR(firstdrv_class_dev)))
		return PTR_ERR(firstdrv_class_dev);
	
	/* ��ַӳ�䣬gpfcon�Ĵ����������ַʱ0X56000050 */
	gpfcon = (volatile unsigned long *)ioremap(0x56000050, 16);
	gpfdat = gpfcon + 1;
	
	return 0;
}

/* ж���������� */
static void __exit first_drv_exit(void)
{
	//printk("first_drv_exit\n");
	unregister_chrdev(MAJOR, "first_drv"); //ж��

	/* ɾ���豸�ڵ� */
	class_device_unregister(firstdrv_class_dev);
	class_destroy(firstdrv_class);

	/* ȡ����ַӳ�� */
	iounmap(gpfcon);
	
	return ;
}

module_init(first_drv_init);
module_exit(first_drv_exit);

MODULE_LICENSE("GPL");
