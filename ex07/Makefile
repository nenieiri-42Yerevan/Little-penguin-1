# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:52:01 by vismaily          #+#    #+#              #
#    Updated: 2023/10/24 16:29:09 by vismaily         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

obj-m		= my_module.o

my_module-y	= /Srcs/id.o /Srcs/main.o

ccflags-y	= -I$(src)/Includes

K-VERSION	= $(shell uname -r)

all:
		mount -t debugfs none /sys/kernel/debug
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) modules

chmod:
		chmod +r /sys/kernel/debug/fortytwo

clean:
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) clean
