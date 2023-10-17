/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:18:25 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/17 12:15:50 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_AUTHOR("Volodya Ismailyan");
MODULE_DESCRIPTION("This is a misc char device driver");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");

dev_t	dev = 0;

static struct class	*dev_class;

static int __init hello_init(void)
{
	/* Allocating Major number dynamically */
	if (alloc_chrdev_region(&dev, 0, 1, "fortytwo") < 0) {
		pr_err("Cannot allocate major number :(\n");
		return (-1);
	}
	pr_info("Major number is %d and Minor number is %d\n",
		MAJOR(dev), MINOR(dev));

	/* Creating struct class */
	dev_class = class_create(THIS_MODULE, "fortytwo_class");
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
	unregister_chrdev_cleanup(dev, 1);
	return (-1);
}

static void __exit hello_cleanup(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev, 1);
	pr_info("Fortytwo device driver removed successfully :)\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
