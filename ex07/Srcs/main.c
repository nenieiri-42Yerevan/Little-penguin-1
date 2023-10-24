/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:18:25 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/24 16:48:45 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_debugfs.h"

MODULE_AUTHOR("Volodya Ismailyan");
MODULE_DESCRIPTION("This is a debugfs module");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");

static struct dentry	*db_fortytwo;
static struct dentry	*db_id;
static struct dentry	*db_jiffies;
static struct dentry	*db_foo;

static int __init debugfs_init(void)
{
	db_fortytwo = debugfs_create_dir("fortytwo", NULL);
	if (!db_fortytwo)
	{
		pr_err("Failed to create 'fortytwo' directory in debugfs");
		return (-1);
	}

	db_id = debugfs_create_file("id", 0666, db_fortytwo, NULL, &fops_id);
	if (!db_fortytwo)
		goto clean_fortytwo;

	db_jiffies = debugfs_create_file("jiffies", 0444, db_fortytwo,
			NULL, NULL);
	if (!db_jiffies)
		goto clean_id;

	db_foo = debugfs_create_file("foo", 0644, db_fortytwo, NULL, NULL);
	if (!db_foo)
		goto clean_jiffies;

	printk(KERN_INFO "Inserting debugfs module!\n");
	return (0);

clean_jiffies:
	debugfs_remove(db_jiffies);
clean_id:
	debugfs_remove(db_id);
clean_fortytwo:
	debugfs_remove(db_fortytwo);
	return (-1);
}

static void __exit debugfs_cleanup(void)
{
	debugfs_remove_recursive(db_fortytwo);
	printk(KERN_INFO "Cleaning up debugfs module.\n");
}

module_init(debugfs_init);
module_exit(debugfs_cleanup);
