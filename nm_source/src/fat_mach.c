/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_mach.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:05:28 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/18 18:20:01 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

t_list		*fat_o(char *bin, size_t bin_size, char arch, char *name)
{
	size_t				len;
	struct fat_arch		*hdr_32;
	struct fat_arch_64	*hdr_64;
	t_list				*list;

	list = NULL;
	len = *(unsigned int*)(bin + 4);
	hdr_32 = (struct fat_arch*)(bin + 8);
	hdr_64 = (struct fat_arch_64*)(bin + 8);
	(void)bin_size;
	while (len)
	{
		printf("\n%s  (for architecture %s)\n", name, get_cpu_type(arch == 64 ?
					hdr_64->cputype : hdr_32->cputype));
		if (arch == 64)
			arch_separator(bin + hdr_64->offset, hdr_64->size, name);
		else
			arch_separator(bin + hdr_32->offset, hdr_32->size, name);
		sort(list);
		print(list, arch);
		free_list(list);
		hdr_32 += 1;
		hdr_64 += 1;
		len -= 1;

	}
	return (NULL);
}
