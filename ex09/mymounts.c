/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymounts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:57:03 by vismaily          #+#    #+#             */
/*   Updated: 2023/11/03 16:10:03 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/list.h>
#include <linux/nsproxy.h>
#include <../fs/mount.h>

MODULE_AUTHOR("Volodya Ismailyan");
MODULE_DESCRIPTION("This is a module about procfs");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");

static struct proc_dir_entry	*mymounts;

/*
 * A 'struct path' is a data structure used in the Linux kernel to represent
 * a path to a file or directory within the filesystem. In this context,
 * it's used to represent the path to a mounted filesystem.
 *
 * dentry : mnt->mnt.mnt_root -> This is the root dir of the mounted filesystem.
 *
 * The purpose of creating 'mnt_path' in this way is to package both the root
 * directory (dentry) and the mount point (mnt) information together for
 * easy access.
 *
 * 'd_sb' is a field within a struct dentry that points to the 'super_block'
 * structure associated with the filesystem represented by that dentry.
 * The 'super_block' contains information about the filesystem type,
 * its operations, and other properties.
 *
 * 'if (sb->s_op->show_devname)' line checks if the super_block structure sb
 * has a function pointer named show_devname defined in its s_op field.
 * The s_op field typically contains the filesystem-specific operations for a
 * given filesystem type. The presence of show_devname indicates that the
 * filesystem type provides a specific function for displaying the device name.
 * If the 'super_block' does not have a 'show_devname' function, the code
 * uses the 'seq_puts' function to write the device name associated with the
 * mounted filesystem to the struct 'seq_file' pointed to by m.
 */
static void show_mount_info(struct seq_file *m, struct mount *mnt)
{
	if (strcmp(mnt->mnt_devname, "rootfs") == 0)
		return ; // Skip the virtual file system (VFS) mount (itself).

	struct path mnt_path = {
		dentry	: mnt->mnt.mnt_root,
		mnt	: &mnt->mnt
	};
	struct super_block *sb = mnt_path.dentry->d_sb;

	if (sb->s_op->show_devname)
		sb->s_op->show_devname(m, mnt_path.dentry);
	else
		seq_puts(m, mnt->mnt_devname ? mnt->mnt_devname : "none");

	seq_putc(m, ' ');
	seq_path(m, &mnt_path, " \t\n\\");
	seq_putc(m, '\n');
}

static int procfs_show(struct seq_file *m, void *v)
{
	struct mount	*mnt;

	list_for_each_entry(mnt, &current->nsproxy->mnt_ns->list, mnt_list) {
		show_mount_info(m, mnt);
	}
	return (0);
}

static int procfs_open(struct inode *inode, struct file *file)
{
	return (single_open(file, procfs_show, NULL));
}

static struct proc_ops	proc_fops = {
	proc_open	: procfs_open,
	proc_read	: seq_read,
	proc_lseek	: seq_lseek,
	proc_release	: single_release
};

static int __init procfs_init(void)
{
	mymounts = proc_create("mymounts", 0444, NULL, &proc_fops);
	if (!mymounts)
	{
		pr_info("Errot when creating the proc device.\n");
		return (-ENOMEM);
	}
	pr_info("Proc device created.\n");
	return (0);
}

static void __exit procfs_exit(void)
{
	remove_proc_entry("mymounts", NULL);
	pr_info("Cleaning up the proc module.\n");
}

module_init(procfs_init);
module_exit(procfs_exit);
