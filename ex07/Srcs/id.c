/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:18:25 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/24 16:48:07 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_debugfs.h"

#define USERNAME	"vismaily"
#define USERNAME_LEN	8

static ssize_t id_read(struct file *f, char __user *buf, size_t len,
				loff_t *offset)
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

static ssize_t id_write(struct file *f, const char __user *buf, size_t len,
				loff_t *offset)
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

const struct file_operations	fops_id = {
	owner	: THIS_MODULE,
	read	: id_read,
	write	: id_write,
};
