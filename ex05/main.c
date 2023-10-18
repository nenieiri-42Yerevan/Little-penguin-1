/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:18:25 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/18 15:51:51 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

MODULE_AUTHOR("Volodya Ismailyan");
MODULE_DESCRIPTION("This is a misc char device driver");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");

static dev_t			dev = 0;
static struct class		*dev_class;
static struct cdev		fortytwo_cdev;
static struct file_operations	fops;

/*
 * This function will be called when we open the Device file
 */
static int fortytwo_open(struct inode *_inode, struct file *_file)
{
	pr_info("1\n");
	return (0);
}

/*
 * This function will be called when we close the Device file
 */
static int fortytwo_release(struct inode *_inode, struct file *_file)
{
	pr_info("2\n");
	return (0);
}

/*
 * This function will be called when we read the Device file
 */
static ssize_t
fortytwo_read(struct file *flip, char __user *buf, size_t len, loff_t *off)
{
	pr_info("3\n");
	return (0);
}

/*
 * This function will be called when we write the Device file
 */
static ssize_t
fortytwo_release(struct file *flip, const char __user *buf,
		size_t len, loff_t *off)
{
	pr_info("4\n");
	return (0);
}

static int __init hello_init(void)
{
	fops.owner = THIS_MODULE;
	fops.open = fortytwo_open;
	fops.read = fortytwo_read;
	fops.write = fortytwo_write;
	fops.release = fortytwo_release;

	cdev_init(&fortytwo_cdev, &fops);

	/* Allocating Major number dynamically */
	if (alloc_chrdev_region(&dev, 0, 1, "fortytwo") < 0) {
		pr_err("Cannot allocate major number :(\n");
		return (-1);
	}
	pr_info("Major number is %d and Minor number is %d\n",
		MAJOR(dev), MINOR(dev));

	/* Adding character device to the system */
	if (cdev_add(&fortytwo_cdev, dev, 1) < 0)
	{
		pr_err("Cannot add the character device to the system\n");
		goto r_class;
	}

	/* Creating struct class */
	dev_class = class_create("fortytwo_class");
	if (IS_ERR(dev_class)) {
		pr_err("Cannot create the struct class for device\n");
		goto r_class;
	}

	/* Creating device */
	if (IS_ERR(device_create(dev_class, NULL, dev, NULL, "fortytwo"))) {
		pr_err("Cannot create the Device\n");
		goto r_device;
	}
	pr_info("Fortytwo device driver inserted successfully :)\n");
	return (0);

r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev, 1);
	return (-1);
}

static void __exit hello_cleanup(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&fortytwo_cdev);
	unregister_chrdev_region(dev, 1);
	pr_info("Fortytwo device driver removed successfully :)\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
