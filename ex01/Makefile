# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:52:01 by vismaily          #+#    #+#              #
#    Updated: 2024/08/15 11:20:57 by vismaily         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

obj-m		= main.o

K-VERSION	= $(shell uname -r)
K-DIR		= /lib/modules/$(K-VERSION)/build

all:
		make -C $(K-DIR) M=$(shell pwd) modules

clean:
		make -C $(K-DIR)  M=$(shell pwd) clean
