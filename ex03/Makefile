# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 17:56:29 by vismaily          #+#    #+#              #
#    Updated: 2023/10/11 18:00:18 by vismaily         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

obj-m		= main.o

K-VERSION	= $(shell uname -r)

all:
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) modules

clean:
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) clean

re:		clean all
