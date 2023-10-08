# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:52:01 by vismaily          #+#    #+#              #
#    Updated: 2023/10/06 14:52:31 by vismaily         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

obj-m		= hello_world.o

K-VERSION	= $(shell uname -r)

all:
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) modules

clean:
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) clean
