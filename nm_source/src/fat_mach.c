/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_mach.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:05:28 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/17 17:47:00 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

t_list		*fat_o(char *bin, size_t bin_size, char arch, char *name)
{
	size_t				len;
	struct fat_arch		*hdr_32;
	struct fat_arch_64	*hdr_64;
	t_list				*rslt;
	size_t				offset;

	offset = 0;
	rslt = NULL;
	len = *(unsigned int*)(bin + 4);
	hdr_32 = (struct fat_arch*)(bin + 8);
	hdr_64 = (struct fat_arch_64*)(bin + 8);
	printf("%s  (for architecture %s)\n", name, get_cpu_type(*(cpu_type_t*)(bin + 8)));
	while (len)
	{
		if (arch == 64)
		{
			rslt = join_list(rslt, mach_o(bin + hdr_64->offset + offset,
						bin_size, arch));
			offset +=
		}
		else
		{
			;
		}
		len -= 1;

	}
	return (mach_o(bin + sizeof(struct fat_header) + (arch == 64 ?
					sizeof( struct fat_arch_64) :
					sizeof(struct fat_arch)), bin_size, arch));
}
