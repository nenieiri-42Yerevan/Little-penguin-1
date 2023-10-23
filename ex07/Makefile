# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:52:01 by vismaily          #+#    #+#              #
#    Updated: 2023/10/23 20:00:02 by vismaily         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

obj-m		= main.o

K-VERSION	= $(shell uname -r)

all:
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) modules
#		chmod +r /sys/kernel/debug/fortytwo

clean:
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) clean
