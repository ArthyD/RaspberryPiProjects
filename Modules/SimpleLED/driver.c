#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/uaccess.h>  
#include <linux/gpio.h>
#include <linux/err.h>

//LED is connected to GPIO 21
#define GPIO_21 21

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ArthyD");
MODULE_DESCRIPTION("Simple driver for LED on raspbian");
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev led_cdev;
 
static int led_driver_init(void);
static void led_driver_exit(void);
static int led_open(struct inode *inode, struct file *file);
static int led_release(struct inode *inode, struct file *file);
static ssize_t led_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t led_write(struct file *filp, const char *buf, size_t len, loff_t * off);

//File operation structure 
static struct file_operations fops =
{
  .owner          = THIS_MODULE,
  .read           = led_read,
  .write          = led_write,
  .open           = led_open,
  .release        = led_release,
};

// open function
static int led_open(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "Device File Opened...!!!\n");
  return 0;
}

// release function
static int led_release(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "Device File Closed...!!!\n");
  return 0;
}

// read function
static ssize_t led_read(struct file *filp, char __user *buf, size_t count, loff_t *off)
{
  printk(KERN_INFO "Read function \n");
  return 0;
}

// write function
static ssize_t led_write(struct file *filp, const char __user *buf, size_t count, loff_t *off)
{
  uint8_t rec_buf[1] = {0};
  
  copy_from_user( rec_buf, buf, count );
    
  printk(KERN_INFO "Write Function\n");
  
  if (rec_buf[0]=='1') {
    //set GPIO to HIGH
    gpio_set_value(GPIO_21, 1);
  } else if (rec_buf[0]=='0') {
    //set GPIO to LOW
    gpio_set_value(GPIO_21, 0);
  } else {
    printk(KERN_INFO "Provide either 1 or 0 \n");
  }
  
  return count;
}

// Init function
static int led_driver_init(void)
{
  /*Allocating Major number*/
  alloc_chrdev_region(&dev, 0, 1, "led");
 
  /*Creating cdev structure*/
  cdev_init(&led_cdev,&fops);
 
  /*Adding character device to the system*/
  cdev_add(&led_cdev,dev,1);
 
  /*Creating struct class*/
  class_create(THIS_MODULE,"led_class");
 
  /*Creating device*/
  device_create(dev_class,NULL,dev,NULL,"led");
  
  //Requesting the GPIO
  gpio_request(GPIO_21,"GPIO_21");
  
  //configure the GPIO as output
  gpio_direction_output(GPIO_21, 0);
  
  gpio_export(GPIO_21, false);
  
  printk(KERN_INFO "Device Driver Insert...Done!!!\n");
 
  
  return 0;
}

// Exit function
static void led_driver_exit(void)
{
  // turn off GPIO
  gpio_set_value(GPIO_21, 0);
  // remove driver 
  gpio_unexport(GPIO_21);
  gpio_free(GPIO_21);
  device_destroy(dev_class,dev);
  class_destroy(dev_class);
  cdev_del(&led_cdev);
  unregister_chrdev_region(dev, 1);
  printk(KERN_INFO "Device Driver Remove...Done!!\n");
}
 
module_init(led_driver_init);
module_exit(led_driver_exit);
 

