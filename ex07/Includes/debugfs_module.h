/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugfs_module.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:29:08 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/24 16:03:43 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGFS_MODULE_H
# define DEBUGFS_MODULE_H

# include <linux/module.h>
# include <linux/kernel.h>
# include <linux/init.h>
# include <linux/debugfs.h>
# include <linux/fs.h>

ssize_t id_read(struct file *f, char __user *buf, size_t len, loff_t *offset);
ssize_t id_write(struct file *f, const char __user *buf, size_t len,
			loff_t *offset);

#endif
