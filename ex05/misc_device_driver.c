/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_device_driver.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:18:25 by vismaily          #+#    #+#             */
/*   Updated: 2023/11/04 19:25:26 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/miscdevice.h>

# define USERNAME	"vismaily"
# define USERNAME_LEN	8

MODULE_AUTHOR("Volodya Ismailyan");
MODULE_DESCRIPTION("This is a misc char device driver");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");

static struct miscdevice	misc_device;
static struct file_operations	fops;

/*
 * This function will be called when we read from the Device
 */
static ssize_t
ft_read(struct file *f, char __user *buf, size_t len, loff_t *offset)
{
	int	readlen;
	size_t	copied;

	if (!buf)
		return -EINVAL;
	if (*offset >= USERNAME_LEN)
		return 0;
	if (*offset + len > USERNAME_LEN)
		readlen = USERNAME_LEN - *offset;
	else
		readlen = len;
	copied = readlen - copy_to_user(buf, USERNAME + *offset, readlen);
	*offset += copied;
	pr_info("Username %s (or it's part) was sent successfully", USERNAME);
	return copied;
}

/*
 * This function will be called when we write to the Device
 */
static ssize_t
ft_write(struct file *f, const char __user *buf,
		size_t len, loff_t *offset)
{
	char	user_data[USERNAME_LEN];

	if (!buf || len != USERNAME_LEN)
		return -EINVAL;
	if (copy_from_user(user_data, buf, len))
		return -EIO;
	if (memcmp(user_data, USERNAME, USERNAME_LEN))
		return -EINVAL;
	pr_info("Username %s was received successfully", USERNAME);
	return len;
}

static int __init ft_driver_init(void)
{
	fops.owner = THIS_MODULE;
	fops.read = ft_read;
	fops.write = ft_write;

	misc_device.minor = MISC_DYNAMIC_MINOR;
	misc_device.name = "fortytwo";
	misc_device.fops = &fops;

	if (misc_register(&misc_device))
	{
		pr_err("misc_register failed!!! :(\n");
		return -1;
	}

	pr_info("Fortytwo misc device driver inserted successfully :)\n");
	return 0;
}

static void __exit ft_driver_exit(void)
{
	misc_deregister(&misc_device);
	pr_info("Fortytwo misc device driver removed successfully :)\n");
}

module_init(ft_driver_init);
module_exit(ft_driver_exit);
