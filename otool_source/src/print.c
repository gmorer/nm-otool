/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:49:14 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/22 15:12:35 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

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

static void	write_content(char *bin, uint64_t place, uint64_t max)
{
	char	i;

	i = 0;
	while (i < 16 && place + i < max)
	{
		if ((*(char*)(place + i + bin) & 0xff) < 16)
			write(1, "0", 1);
		print_address(*(char*)(place + i + bin) & 0xff);
		write(1, " ", 1);
		i++;
	}
	return ;
}

void		print(char *bin, t_section sect, char arch)
{
	uint64_t	i;
	uint64_t	tmp;
	char		count;

	i = 0;
	write(1, "Contents of (__TEXT,__text) section\n", 36);
	while (i < sect.size)
	{
		count = 0;
		tmp = i + sect.addr;
		while (tmp > 15)
		{
			tmp /= 16;
			count++;
		}
		write(1, "0000000000000000", arch == 64 ? 15 - count : 7 - count);
		print_address(i + sect.addr);
		write(1, "\t", 1);
		write_content(bin, i + sect.offset, sect.size + sect.offset);
		write(1, "\n", 1);
		i += 16;
	}
	return ;
}
