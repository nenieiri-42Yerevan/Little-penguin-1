/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:18:25 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/20 18:09:52 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

# define USERNAME	"vismaily"
# define USERNAME_LEN	8

MODULE_AUTHOR("Volodya Ismailyan");
MODULE_DESCRIPTION("This is a misc char device driver");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");

static dev_t			dev = 0;
static struct class		*dev_class;
static struct cdev		ft_cdev;
static struct file_operations	fops;

/*
 * This function will be called when we read from the Device
 */
static ssize_t
ft_read(struct file *f, char __user *buf, size_t len, loff_t *offset)
{
	int	readlen;
	size_t	copied;

	if (!buf)
		return (-EINVAL);
	if (*offset >= USERNAME_LEN)
		return (0);
	if (*offset + len > USERNAME_LEN)
		readlen = USERNAME_LEN - *offset;
	else
		readlen = len;
	copied = readlen - copy_to_user(buf, USERNAME + *offset, readlen);
	*offset += copied;
	pr_info("Username %s (or it's part) was sent successfully", USERNAME);
	return (copied);
}

/*
 * This function will be called when we write to the Device
 */
static ssize_t
ft_write(struct file *f, const char __user *buf,
		size_t len, loff_t *offset)
{
	char	user_data[USERNAME_LEN];

	if (!buf || len != USERNAME_LEN)
		return (-EINVAL);
	if (copy_from_user(user_data, buf, len))
		return (-EIO);
	if (memcmp(user_data, USERNAME, USERNAME_LEN))
		return (-EINVAL);
	pr_info("Username %s was received successfully", USERNAME);
	return (len);
}

static int __init driver_init(void)
{
	fops.owner = THIS_MODULE;
	fops.read = ft_read;
	fops.write = ft_write;

	cdev_init(&ft_cdev, &fops);

	/* Allocating Major number dynamically */
	if (alloc_chrdev_region(&dev, 0, 1, "fortytwo") < 0) {
		pr_err("Cannot allocate major number :(\n");
		return (-1);
	}
	pr_info("Major number is %d and Minor number is %d\n",
		MAJOR(dev), MINOR(dev));

	/* Adding character device to the system */
	if (cdev_add(&ft_cdev, dev, 1) < 0)
	{
		pr_err("Cannot add the character device to the system\n");
		goto r_class;
	}

	/* Creating struct class */
	dev_class = class_create("ft_class");
	if (IS_ERR(dev_class)) {
		pr_err("Cannot create the struct class for device\n");
		goto r_cdev;
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
r_cdev:
	cdev_del(&ft_cdev);
r_class:
	unregister_chrdev_region(dev, 1);
	return (-1);
}

static void __exit driver_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&ft_cdev);
	unregister_chrdev_region(dev, 1);
	pr_info("Fortytwo device driver removed successfully :)\n");
}

module_init(driver_init);
module_exit(driver_exit);
