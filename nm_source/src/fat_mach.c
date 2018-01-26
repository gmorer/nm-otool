/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_mach.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:05:28 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/23 12:02:20 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

static void	ft_putstr(char *str)
{
	int i;

	if (!str)
		return;
	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

static		int not_present_before(char *bin, size_t n, char arch)
{
	unsigned int	cpu;
	size_t			i;

	cpu = *(unsigned int*)(bin + 8 + (n * (arch == 64 ? 24 : 20)));
	i = 0;
	while (i < n)
	{
		if (*(unsigned int*)(bin + 8 + (i * (arch == 64 ? 24 : 20))) == cpu)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static		int count_bin(char *bin, size_t bin_size, char arch)
{
	size_t i;
	struct fat_arch     *hdr_32;
	struct fat_arch_64  *hdr_64;
	size_t len;
	size_t rslt;

	i = 0;
	rslt = 0;
	len = *(unsigned int*)(bin + 4);
	hdr_32 = (struct fat_arch*)(bin + 8);
	hdr_64 = (struct fat_arch_64*)(bin + 8);
	while (i < len && i * (arch == 64 ? sizeof(*hdr_64) : sizeof(*hdr_32)) + 8 < bin_size)
	{
		if (not_present_before(bin, i, arch))
			rslt++;
		i++;
	}
	return (rslt);
}

t_list		*fat_o(char *bin, size_t bin_size, char arch, char *name)
{
	size_t				len;
	struct fat_arch		*hdr_32;
	struct fat_arch_64	*hdr_64;
	t_list				*list;
	size_t				i;

	i = 0;
	list = NULL;
	len = count_bin(bin, bin_size, arch);
	hdr_32 = (struct fat_arch*)(bin + 8);
	hdr_64 = (struct fat_arch_64*)(bin + 8);
	(void)bin_size;
	while (len && i * (arch == 64 ? sizeof(*hdr_64) : sizeof(*hdr_32)) + 8 < bin_size)
	{
		if (count_bin(bin, bin_size, arch) > 1)
		{
			write(1, "\n", 1);
			ft_putstr(name);
			write(1, " (for architecture ", 19);
			ft_putstr(get_cpu_type(arch == 64 ? hdr_64->cputype : hdr_32->cputype));
			write(1, "):\n", 3);
		}
		if (not_present_before(bin, i, arch))
		{
			if (arch == 64)
				arch_separator(bin + hdr_64->offset, hdr_64->size, name);
			else
				arch_separator(bin + hdr_32->offset, hdr_32->size, name);
			sort(list);
			print(list, arch);
			free_list(list);
			len -= 1;
		}
		i++;
		hdr_32 += 1;
		hdr_64 += 1;
	}
	return (NULL);
}
