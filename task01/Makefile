# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:52:01 by vismaily          #+#    #+#              #
#    Updated: 2023/10/06 12:57:30 by vismaily         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ-M		= hello_wolrd.c

K-VERSION	= $(shell uname -r)

all:
		make -C /lib/modules/$(K-VERSION)/build M=$(pwd) modules

clean:
		make -C /lib/modules/$(K-VERSION)/build M=$(pwd) clean
