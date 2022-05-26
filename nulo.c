#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>

#define DEVICE_NAME "devNulo"

ssize_t my_read(struct file *filp, char *data, size_t s, loff_t *off){
    return 0;
}

ssize_t my_write(struct file *filp, const char *data, size_t s, loff_t *off){
    return 0;
}

static struct cdev dev;
dev_t major;
static struct class *mi_class;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = my_read,
    .write = my_write,
    .open = NULL,
    .release = NULL, 
};

static int __init nulo_init(void) {
	printk(KERN_ALERT "Hola, soy nulo!\n");
    cdev_init(&dev, &fops);
    
    //2
    alloc_chrdev_region(&major, 0, 1, DEVICE_NAME);
    cdev_add(&dev, major, 1);

    mi_class = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(mi_class, NULL, major, NULL, DEVICE_NAME);

	return 0;
}

static void __exit nulo_exit(void) {
	printk(KERN_ALERT "Adios, aunque no haya hecho nada\n");
    unregister_chrdev_region(major, 1);
    cdev_del(&dev);
    device_destroy(mi_class, major);
    class_destroy(mi_class);
}

module_init(nulo_init);
module_exit(nulo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("No hago nada y nada me importa.");
