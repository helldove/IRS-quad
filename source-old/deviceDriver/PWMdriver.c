#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <asm/uaccess.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/PWMdriver.h>
#include "PWMdriver.h"

#define ENABLE_PWM		_IOW('q',1,pwmData *)
#define DISABLE_PWM		_IOW('q',2,pwmData *)

typedef struct{
	unsigned int Channel;
	unsigned int Freq;
	unsigned int Period;
}PWMdata;

struct pwm_device{
	struct list_head 		node;
	struct platform_device	*pdev;
	struct platform_device	*colibripwm_dev;
	const char				*label;
	struct clk				*clk;

	int 					clk_enb;
	void __iomem			*mmio_base;

	unsigned int 			in_use;
	unsigned int 			id;
};

struct pwm_driver{
	unsigned int period[PWM_CHANNELS];
	unsigned int PWMID[PWM_CHANNELS];
	struct pwm_device *pwmdev[PWM_CHANNELS];
};

static dev_t first;
static struct cdev c_dev;
static struct class *cl;
static int init_result;
static strucdt pwm_driver *pwmDriver;

static ssize_t pwm_read(struct file *F, char *buf, size_t count, loff_t *f_pos){
	return -EPERM;
}
static ssize_t pwm_write(struct file *F, char *buf, size_t count, loff_t *f_pos){
	return -EPERM;
}
static int pwm_open(struct inode *inode, struct file *file)
{
    return 0;
}
 
static int pwm_close(struct inode *inode, struct file *file)
{
    return 0;
}
 
static long pwm_device_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
    int retval;
    pwmData data;
 
    switch (cmd)
    {
        case ENABLE_PWM:
        if (copy_from_user(&data, (pwmData*)arg, sizeof(pwmData)))
        {
            return -EFAULT;
        }
        retval = pwm_config(pwmDriver->pwmdev[data.pwmChannel - 1], data.pwmDutyCycle, data.pwmPeriod);
        if (retval == 0)
        {
            retval = pwm_enable(pwmDriver->pwmdev[data.pwmChannel - 1]);
            return retval;
        }
        else
        {
            return retval;
        }
        break;
 
        case DISABLE_PWM:
        if (copy_from_user(&data, (pwmData*)arg, sizeof(pwmData)))
        {
            return -EFAULT;
        }
        retval = pwm_config(pwmDriver->pwmdev[data.pwmChannel - 1], 0, data.pwmPeriod);
        if (retval == 0)
        {
            pwm_disable(pwmDriver->pwmdev[data.pwmChannel - 1]);
        }
        else
        {
            return retval;
        }
        break;
 
        default:
            break;
    }
 
     return 0;
}
 
static int pwm_device_probe(struct platform_device *pdev)
{
    int i, ret = 0;
 
    pwmDriver = kzalloc(sizeof(struct pwm_driver), GFP_KERNEL);
 
    if (!pwmDriver)
    {
        printk(KERN_ALERT "Platform get drvdata returned NULL\n");
        return -ENOMEM;
    }
 
    for (i = 1; i < PWM_CHANNELS; i++)
    {
        switch (i)
        {
            case 0:
                pwmDriver->pwmdev[0] = pwm_request(0, "PWM_1");
            break;
 
            case 1:
                pwmDriver->pwmdev[1] = pwm_request(1, "PWM_2");
            break;
 
            case 2:
                pwmDriver->pwmdev[2] = pwm_request(2, "PWM_3");
            break;
 
            case 3:
                pwmDriver->pwmdev[3] = pwm_request(3, "PWM_4");
            break;
 
            default:
                break;
        }
        if (IS_ERR(pwmDriver->pwmdev[i])) {
            ret = PTR_ERR(pwmDriver->pwmdev[i]);
            dev_err(&pdev->dev, "unable to request PWM %d\n", i);
            goto err;
        }
    }
 
    platform_set_drvdata(pdev, pwmDriver);
 
    return 0;
 
err:
    if (i > 0) {
        for (i = i - 1; i >= 1; i--) {
            pwm_free(pwmDriver->pwmdev[i]);
    }
}
 
kfree(pwmDriver);
 
return ret;
}
 
static int pwm_device_remove(struct platform_device *pdev)
{
    int i;
    for (i = 1; i < PWM_CHANNELS; i++) {
        pwm_free(pwmDriver->pwmdev[i]);
    }
    printk("PWM Platform Device removed\n");
    return 0;
}
 
static struct platform_driver pwm_driver = {
    .probe = pwm_device_probe,
    .remove = pwm_device_remove,
    .driver = {
        .name = "colibri_pwm",
        .owner = THIS_MODULE,
    },
};
 
static struct file_operations FileOps =
{
    .owner                = THIS_MODULE,
    .open                 = pwm_open,
    .read                 = pwm_read,
    .write                = pwm_write,
    .release              = pwm_close,
    .unlocked_ioctl       = pwm_device_ioctl,
};
 
static int pwm_init(void)
{
    init_result = platform_driver_probe(&pwm_driver, &pwm_device_probe);
 
    if (init_result < 0)
    {
        printk(KERN_ALERT "PWM Platform Driver probe failed with :%d\n", init_result);
        return -1;
    }
    else
    {
        init_result = alloc_chrdev_region( &first, 0, 1, "pwm_drv" );
        if( 0 > init_result )
        {
            platform_driver_unregister(&pwm_driver);
            printk( KERN_ALERT "PWM Device Registration failed\n" );
            return -1;
        }
        if ( (cl = class_create( THIS_MODULE, "chardev" ) ) == NULL )
        {
            platform_driver_unregister(&pwm_driver);
            printk( KERN_ALERT "PWM Class creation failed\n" );
            unregister_chrdev_region( first, 1 );
            return -1;
        }
 
        if( device_create( cl, NULL, first, NULL, "pwm_drv" ) == NULL )
        {
            platform_driver_unregister(&pwm_driver);
            printk( KERN_ALERT "PWM Device creation failed\n" );
            class_destroy(cl);
            unregister_chrdev_region( first, 1 );
            return -1;
        }
 
        cdev_init( &c_dev, &FileOps );
 
        if( cdev_add( &c_dev, first, 1 ) == -1)
        {
            platform_driver_unregister(&pwm_driver);
            printk( KERN_ALERT "PWM Device addition failed\n" );
            device_destroy( cl, first );
            class_destroy( cl );
            unregister_chrdev_region( first, 1 );
            return -1;
        }
    }
 
    return 0;
}
 
static void pwm_exit(void)
{
    platform_driver_unregister(&pwm_driver);
    kfree(pwmDriver);
    cdev_del( &c_dev );
    device_destroy( cl, first );
    class_destroy( cl );
    unregister_chrdev_region( first, 1 );
 
    printk(KERN_ALERT "PWM Driver unregistered\n");
}
 
module_init(pwm_init);
module_exit(pwm_exit);
 
MODULE_AUTHOR("Sanchayan Maity");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Colibri T20 PWM Driver");