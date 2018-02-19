/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 11:55:46 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/19 17:18:53 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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

static void	print_address(void *addr)
{
	long	n;

	n = (long)addr;
	if (n < 16)
		print_hex(n);
	else if (n > 9)
	{
		print_address((void*)(n / (long)16));
		print_address((void*)(n % (long)16));
	}
}

static void	print_o(size_t offset, char arch)
{
	int		i;
	size_t	save;

	i = 0;
	save = offset;
	while (offset > 15)
	{
		offset = offset / 16;
		i++;
	}
	write(1, "0000000000000000", arch == 64 ? 15 - i : 7 - i);
	print_address((void*)save);
}

void		print(t_list *list, char arch)
{
	while (list)
	{
		if (list->data.type == 'U' || list->data.type == 'u')
			write(1, "                ", arch == 32 ? 8 : 16);
		else
			print_o(list->data.offset, arch);
		write(1, " ", 1);
		write(1, &(list->data.type), 1);
		write(1, " ", 1);
		ft_putstr(list->data.name);
		write(1, "\n", 1);
		list = list->next;
	}
}
