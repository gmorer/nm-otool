/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:15:36 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/22 15:11:41 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbin.h"

static char	*reverse_endian(char *bin, size_t len)
{
	size_t	i;
	int32_t	*data;

	i = 0;
	len = len / 4;
	data = (void*)bin;
	while (i < len)
	{
		data[i] = ((data[i] & 0xff000000) >> 24) |
			((data[i] & 0x00ff0000) >> 8) |
			((data[i] & 0x0000ff00) << 8) | (data[i] << 24);
		i += 1;
	}
	return (bin);
}

static char	*swap_fat(char *bin, size_t size, int arch)
{
	reverse_endian(bin, 8);
	reverse_endian(bin + 8, *(unsigned int*)(bin + 4) * (arch == 64 ?
				sizeof(struct fat_arch) : sizeof(struct fat_arch_64)));
	(void)size;
	(void)arch;
	return (bin);
}

static char	*swap_mach_o(char *bin, size_t size, int arch)
{
	struct mach_header		*hdr;
	struct symtab_command	*sym;

	reverse_endian(bin, size);
	hdr = (struct mach_header*)bin;
	if ((sym = (struct symtab_command*)get_symtab(bin, size, arch)) == NULL)
		return (NULL);
	reverse_endian(bin + sym->stroff, sym->strsize);
	return (bin);
}

char		*endian_auto_reverse(char *bin, size_t size)
{
	if (*(unsigned int*)bin == MH_CIGAM)
		return (swap_mach_o(bin, size, 32));
	else if (*(unsigned int*)bin == MH_CIGAM_64)
		return (swap_mach_o(bin, size, 64));
	else if (*(unsigned int*)bin == FAT_CIGAM)
		return (swap_fat(bin, size, 32));
	else if (*(unsigned int*)bin == FAT_CIGAM_64)
		return (swap_fat(bin, size, 64));
	return (bin);
}
