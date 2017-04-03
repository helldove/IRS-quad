#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/miscdevice.h>

#define DEVICE_NAME	"GPIO_LED"
#define DEVICE_MAJOR	500

#define PERIPH_BASE	0xC8834000
#define GPIO_BASE	0x400
#define GPIOXY_BASE	0xC8834400
#define GPIOX_OEN	0x18
#define GPIOX_OUT	0x19
#define GPIOX_IN	0x1A
#define GPIOX_PULLEN	0x4C
#define GPIOX_PULL	0x3E

#define GPIO_READ_MODE	3
#define GPIO_WRITE_MODE	1

int gpioInit(void);
void gpioExit(void);
int gpioOpen(struct inode *node, struct file *flip);
int gpioClose(struct inode *node, struct file *flip);
ssize_t gpioXRead(struct file *flip, char *data, size_t size, loff_t *offet);
ssize_t gpioXWrite(struct file *flip, const char *data, size_t size, loff_t *offset);
long gpioXioctl(struct file *flip, unsigned int cmd, unsigned long arg);

static void __iomem *control;
static void __iomem *mmio;
struct file_operations ledCtrlFop = {
	.read = gpioXRead,
	.write = gpioXWrite,
	.open = gpioOpen,
	.release = gpioClose,
	.unlocked_ioctl = gpioXioctl
};

struct miscdevice ledDevice = {
	.minor = 0,
	.fops = &ledCtrlFop,
	.name = DEVICE_NAME
};

int gpioOpen(struct inode *node, struct file *flip){
	
	return 0;	
}

int gpioInit(void){
	unsigned int temp;
	int rval;
	
	mmio = ioremap(PERIPH_BASE,0x1FFF);
	control = (void __iomem *)(mmio + GPIO_BASE + (GPIOX_OEN<<2));
	
	if((rval=register_chrdev(DEVICE_MAJOR,DEVICE_NAME,&ledCtrlFop))<0){
		printk("error at register_chrdev()\n");
		iounmap((void *)mmio);
		return rval;}
	else
		printk("load gpioDD succeded\n");
	
	temp = ioread32(control);
	iowrite32(temp & ~(0x003FFFFF),control);
	control =(void __iomem *)(mmio + GPIO_BASE + (GPIOX_OUT<<2));
	temp = ioread32(control);
	iowrite32(temp | 0x003FFFFF,control);
	control = (void __iomem *)(mmio + GPIO_BASE + (GPIOX_PULLEN<<2));
	temp = ioread32(control);
	iowrite32(temp | 0x003FFFFF,control);
	control = (void __iomem *)(mmio + GPIO_BASE + (GPIOX_PULL<<2));
	temp = ioread32(control);
	iowrite32(temp | 0x003FFFFF,control);
	
	misc_register(&ledDevice);

	return 0;
}
void gpioExit(void){
	unsigned int temp;
	control = (void __iomem *)(mmio + GPIO_BASE + (GPIOX_OUT<<2));
	temp = ioread32(control);
	iowrite32(temp & ~(0x003FFFFF),control);
	control = (void __iomem *)(mmio + GPIO_BASE + (GPIOX_PULLEN<<2));
	temp = ioread32(control);
	iowrite32(temp & ~(0x003FFFFF),control);
	control = (void __iomem *)(mmio + GPIO_BASE + (GPIOX_PULL<<2));
	temp = ioread32(control);
	iowrite32(temp & ~(0x003FFFFF),control);
	misc_deregister(&ledDevice);
	iounmap((void *)mmio);
	unregister_chrdev(DEVICE_MAJOR,DEVICE_NAME);
	printk("unload gpioDD succeded\n");
}

module_init(gpioInit);
module_exit(gpioExit);
	
int gpioClose(struct inode *node, struct file *flip){
	return 0;
}

ssize_t gpioXRead(struct file *flip, char *data, size_t size, loff_t *offet){
	unsigned int temp;
	if(size < 4)
		return -1;
	control = (void __iomem *)(mmio + GPIO_BASE + (GPIOX_IN<<2));
	temp = ioread32(control);
	data[0] = temp&0xFF000000>>24;
	data[1] = temp&0x00FF0000>>16;
	data[2] = temp&0x0000FF00>>16;
	data[3] = temp&0x000000FF;

	return 0;
}

ssize_t gpioXWrite(struct file *flip, const char *data, size_t size, loff_t *offset){
	unsigned int temp,locate;
	if(data[0] == 'a')
		locate = 0x003FFFFF;
	else
		locate = 1<<data[0];
	
	control = (void __iomem *)(mmio + GPIO_BASE + (GPIOX_OUT<<2));
	temp = ioread32(control);
	iowrite32(temp | locate,control);
	return 0;

}

long gpioXioctl( struct file *flip, unsigned int cmd, unsigned long arg){
	unsigned int temp = 0;
	printk("input cmd : %d\n",cmd);
	switch(cmd){
		case GPIO_READ_MODE:
			control = (void __iomem *)(mmio + GPIO_BASE + (GPIOX_OEN<<2));
			temp = ioread32(control);
			iowrite32(temp | 0x003FFFFF,control);
			control =(void __iomem *)(mmio + GPIO_BASE + (GPIOX_OUT<<2));
			temp = ioread32(control);
			iowrite32(temp & ~(0x003FFFFF),control);
			control = (void __iomem *)(mmio + GPIO_BASE + (GPIOX_PULLEN<<2));
			temp = ioread32(control);
			iowrite32(tem.           dG}I}I  G}I D    ..          dG}I}I  G}I      B. m   ���� o������������  ����A d a p t  oi v e F u n   c 1 ADAPTI~1M    dL}I~I  q}IDJ   B. m   ���� �������������  ����A d a p t  �i v e F u n   c 2 ADAPTI~2M    dL}I~I  zr}IDt   Bm   ������ /������������  ����A d a p t  /i v e L a w   1 . ADAPTI~3M    dL}I~I  Oq}IDg   B. m   ���� �������������  ����A d a p t  �i v e L a w   2 C ADAPTI~4M    dL}I~I  �~}IDL   B. m   ���� �������������  ����A d a p t  �i v e L a w   2 M ADAPTI~5M    dL}I~I  �~}IDL   B2 . m   �� ������������  ����A d a p t  i v e S i m   u l ADAPTI~6M    dL}I~I  �~}ID�  B1 . m   �� �������������  ����a d a p t  �i v e S i m   u l ADAPTI~7M    dL}I~I  Tq}IDt                                                                                