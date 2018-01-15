/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 11:55:46 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/15 16:19:10 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	ft_putstr(char *str)
{
	size_t i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	return ;
}

static void print_o(size_t offset)
{
	int		i;
	char	*tab = "0000000000000000";

	i = 0;
	while (offset > 10)
	{
		offset = offset / 16;
		i++;
	}
	write(1, tab, 15 - i);
}

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

void		print(t_list *list)
{
	while(list)
	{
		if (list->data.offset == 0)
			write(1, "                ", 16);
		else
		{
			print_o(list->data.offset);
			print_address((void*)list->data.offset);
		}
		if (list->data.type == 15)
			write(1, " T ", 3);
		else if (list->data.type == 14)
			write(1, " t ", 3);
		else if (list->data.type == 1)
			write(1, " U ", 3);
		else
			write(1, " ? ", 3);
		ft_putstr(list->data.name);
		write(1, "\n", 1);
		list = list->next;
	}
}
