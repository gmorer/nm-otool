/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_o.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:32:00 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/22 13:24:22 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

#define CPU_ARCH_ABI64  0x01000000

static int	is_good(char *bin, size_t n, char arch)
{
	unsigned int	cpu;
	size_t			i;

	cpu = *(unsigned int*)(bin + 8 + (n * (arch == 64 ? 24 : 20)));
	i = 0;
	while (i < *(unsigned int*)(bin + 4))
	{
		if (i != n)
		{
			if (*(unsigned int*)(bin + 8 + (i * (arch == 64 ? 24 : 20))) == cpu)
				return (0);
			if (*(unsigned int*)(bin + 8 + (i * (arch == 64 ? 24 : 20))) ==
					(cpu | CPU_ARCH_ABI64))
				return (0);
			if ((*(unsigned int*)(bin + 8 + (i * (arch == 64 ? 24 : 20))) |
						CPU_ARCH_ABI64) == cpu)
				return (1);
		}
		i++;
	}
	return (1);
}

static int	count_bin(char *bin, size_t bin_size, char arch)
{
	size_t				i;
	struct fat_arch		*hdr_32;
	struct fat_arch_64	*hdr_64;
	size_t				len;
	size_t				rslt;

	i = 0;
	rslt = 0;
	len = *(unsigned int*)(bin + 4);
	hdr_32 = (struct fat_arch*)(bin + 8);
	hdr_64 = (struct fat_arch_64*)(bin + 8);
	while (i < len && i * (arch == 64 ? sizeof(*hdr_64) :
				sizeof(*hdr_32)) + 8 < bin_size)
	{
		if (is_good(bin, i, arch))
			rslt++;
		i++;
	}
	return (rslt);
}

static void	print_header(char *name, cpu_type_t cputype)
{
	write(1, "\n", 1);
	ft_putstr(name);
	write(1, " (for architecture ", 19);
	ft_putstr(get_cpu_type(cputype));
	write(1, "):\n", 3);
	return ;
}

static void	init_fato(size_t *i, struct fat_arch_64 **hdr_64,
		struct fat_arch **hdr_32, char *bin)
{
	*i = 0;
	*hdr_32 = (struct fat_arch*)(bin + 8);
	*hdr_64 = (struct fat_arch_64*)(bin + 8);
	return ;
}

void		fat_o(char *bin, size_t bin_size, char arch, char *name)
{
	size_t				len;
	struct fat_arch		*hdr_32;
	struct fat_arch_64	*hdr_64;
	size_t				i;

	len = count_bin(bin, bin_size, arch);
	init_fato(&i, &hdr_64, &hdr_32, bin);
	while (len && i * (arch == 64 ? sizeof(*hdr_64) : sizeof(*hdr_32))
			+ 8 < bin_size)
	{
		if (count_bin(bin, bin_size, arch) > 1)
			print_header(name, hdr_32->cputype);
		if (is_good(bin, i, arch))
		{
			if (arch == 64)
				arch_separator(bin + hdr_64->offset, hdr_64->size, name);
			else
				arch_separator(bin + hdr_32->offset, hdr_32->size, name);
			len -= 1;
		}
		i++;
		hdr_32 += 1;
		hdr_64 += 1;
	}
	return ;
}
