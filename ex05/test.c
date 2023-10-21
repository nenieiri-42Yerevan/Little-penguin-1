/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .for_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:57:36 by vismaily          #+#    #+#             */
/*   Updated: 2023/10/20 18:07:34 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	name[8];
	int	fd;
	int	res;

	memset(name, 0, 8);

	fd = open("/dev/fortytwo", O_RDWR);

	res = write(fd, "vism", 4);
	printf("res - %d\n", res);

	res = write(fd, "vismaily", 8);
	printf("res - %d\n", res);

	res = read(fd, name, 2);
	printf("res - %s | %d\n", name, res);

	res = read(fd, name, 2);
	printf("res - %s | %d\n", name, res);

	res = read(fd, name, 8);
	printf("res - %s | %d\n", name, res);

	res = read(fd, name, 8);
	printf("res - %s | %d\n", name, res);

	return (0);
}
