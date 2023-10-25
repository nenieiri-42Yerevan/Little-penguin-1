/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_debugfs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:29:08 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/25 14:46:19 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_DEBUGFS_H
# define MY_DEBUGFS_H

# include <linux/module.h>
# include <linux/kernel.h>
# include <linux/init.h>
# include <linux/debugfs.h>
# include <linux/fs.h>
# include <linux/jiffies.h>
# include <linux/err.h>
# include <linux/mutex.h>

extern const struct file_operations	fops_id;
extern const struct file_operations	fops_foo;

#endif
