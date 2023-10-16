/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:18:25 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/16 13:42:06 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

MODULE_AUTHOR("Volodya Ismailyan");
MODULE_DESCRIPTION("This is a misc char device driver");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");

dev_t	dev = 0;

static int __init hello_init(void)
{
	if (alloc_chrdev_region(&dev, 0, 1, "fortytwo") < 0)
	{
		pr_info("Cannot allocate major number :(\n");
		return (-1);
	}
	pr_info("Major number is %d and Minor number is %d\n",
		MAJOR(dev), MINOR(dev));
	pr_info("Fortytwo device driver inserted successfully :)\n");
	return (0);
}

static void __exit hello_cleanup(void)
{
	unregister_chrdev_region(dev, 1);
	pr_info("Fortytwo device driver removed successfully :)\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
