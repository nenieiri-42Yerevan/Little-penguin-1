/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:18:25 by vismaily          #+#    #+#             */
/*   Updated: 2024/08/15 11:43:56 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>

MODULE_AUTHOR("Volodya Ismailyan");
MODULE_DESCRIPTION("This is a Hello_world module");
MODULE_VERSION("1:0.0");
MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");

static int __init hello_init(void)
{
	printk(KERN_INFO "Hello world !\n");
	return 0;
}

static void __exit hello_cleanup(void)
{
	printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
