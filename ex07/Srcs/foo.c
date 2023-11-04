/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:44:37 by vismaily          #+#    #+#             */
/*   Updated: 2023/11/04 19:27:23 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_debugfs.h"

static char	foo_buff[PAGE_SIZE];
static size_t	foo_buff_len = 0;

DEFINE_MUTEX(foo_mutex);

static ssize_t foo_read(struct file *f, char __user *buf, size_t len,
			loff_t *offset)
{
	int	readlen;
	int	copied;

	mutex_lock(&foo_mutex);
	if (!buf)
	{
		mutex_unlock(&foo_mutex);
		return -EINVAL;
	}
	
	if (*offset >= foo_buff_len)
	{
		mutex_unlock(&foo_mutex);
		return 0;
	}

	if (len + *offset >= foo_buff_len)
		readlen = foo_buff_len - *offset;
	else
		readlen = len;

	copied = readlen - copy_to_user(buf, foo_buff + *offset, readlen);
	*offset += copied;
	mutex_unlock(&foo_mutex);
	return copied;
}

static ssize_t foo_write(struct file *f, const char __user *buf, size_t len,
			loff_t *offset)
{
	int	not_copied;

	mutex_lock(&foo_mutex);
	if (len > PAGE_SIZE) {
		mutex_unlock(&foo_mutex);
		return -EINVAL;
	}

	not_copied = copy_from_user(foo_buff, buf, len);
	if (not_copied)
	{
		mutex_unlock(&foo_mutex);
		foo_buff_len = len - not_copied;
		return -EFAULT;
	}

	foo_buff_len = len;
	mutex_unlock(&foo_mutex);
	return len;
}

const struct file_operations	fops_foo = {
	owner	: THIS_MODULE,
	read	: foo_read,
	write	: foo_write,
};
