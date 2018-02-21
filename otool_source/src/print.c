/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:49:14 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/21 16:32:50 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

#include <stdio.h>

static void	print_hex(char c)
{
	if (c < 10)
	{
		c += 48;
		write(1, &c, 1);
	}
	else
	{
		c += 87;
		write(1, &c, 1);
	}
}

static void	print_address(uint64_t addr)
{
	uint64_t	n;

	n = addr;
	if (n < 16)
		print_hex(n);
	else if (n > 9)
	{
		print_address(n / 16);
		print_address(n % 16);
	}
}

void	print(char *bin, uint64_t tab, uint64_t size)
{
	uint64_t i;
	int		off;

	off = 0;
	i = tab;
	while (i < size + tab)
	{
		print_address(i + off);
		write(1, "\n", 1);
		printf("%.16llx\n", i + (int)0);
		i += 16;
	}
	return ;
}
