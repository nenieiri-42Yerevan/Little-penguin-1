# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:52:01 by vismaily          #+#    #+#              #
#    Updated: 2024/08/29 11:00:55 by vismaily         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

obj-m		= my_module.o

my_module-y	= /Srcs/id.o /Srcs/main.o /Srcs/foo.o

ccflags-y	= -I$(src)/Includes

K-VERSION	= $(shell uname -r)

all:
#		mount -t debugfs none /sys/kernel/debug
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) modules

chmod:
		chmod +r /sys/kernel/debug

clean:
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) clean

re:		clean all
