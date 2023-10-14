/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:18:25 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/14 22:42:33 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_AUTHOR("Volodya Ismailyan");
MODULE_DESCRIPTION("This is a keyboard driver");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");

static int __init init_driver(void)
{
	pr_info("Keyboard plugged in!\n");
	return (0);
}

static void __exit cleanup_driver(void)
{
	pr_info("Cleaning up module.\n");
}

module_init(init_driver);
module_exit(cleanup_driver);
