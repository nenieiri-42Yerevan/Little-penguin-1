/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:18:25 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/22 22:46:58 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/debugfs.h>

MODULE_AUTHOR("Volodya Ismailyan");
MODULE_DESCRIPTION("This is a debugfs module");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");

static struct dentry	*ft_dentry;

static int __init debugfs_init(void)
{
	ft_dentry = debugfs_create_dir("fortytwo", NULL);
	if (!ft_dentry)
	{
		pr_err("Failed to create 'fortytwo' directory in debugfs");
		return (-1);
	}
	printk(KERN_INFO "Inserting debugfs module!\n");
	return (0);
}

static void __exit debugfs_cleanup(void)
{
	debugfs_remove_recursive(ft_dentry);
	printk(KERN_INFO "Cleaning up debugfs module.\n");
}

module_init(debugfs_init);
module_exit(debugfs_cleanup);
