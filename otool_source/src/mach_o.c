/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:19:58 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/21 16:32:42 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include <stdio.h>

#define NSECTS_64 (int)(&((struct segment_command_64*)(0x0))->nsects)
#define NSECTS_32 (int)(&((struct segment_command*)(0x0))->nsects)
#define HDR_NCMDS (int)(&((struct mach_header*)(0x0))->ncmds)

static uint64_t	check_segment(void *addr, char arch, uint64_t *size)
{
	struct section_64	*sect_64;
	struct section		*sect_32;
	size_t				i;

	i = 0;
	sect_32 = (void*)(addr + (arch == 64 ? sizeof(struct segment_command_64) :
				sizeof(struct segment_command)));
	sect_64 = (void*)sect_32;
	while (i < *((unsigned int*)((void*)addr +
					(arch == 64 ? NSECTS_64 : NSECTS_32))))
	{
		if (!ft_strcmp(arch == 64 ? sect_64->sectname : sect_32->sectname, "__text"))
		{
			*size = arch == 64 ? sect_64->size : sect_32->size;
			return (arch == 64 ? sect_64->offset : sect_32->offset);
		}
		sect_32 += 1;
		sect_64 += 1;
		i += 1;
	}
	return (0);
}

static uint64_t	get_secttab(char *bin, size_t bin_size, char arch, uint64_t *size)
{
	struct load_command		*lc;
	unsigned int			index;
	size_t					i;
	uint64_t				rslt;

	index = 0;
	lc = (void*)bin + (arch == 32 ? sizeof(struct mach_header) :
			sizeof(struct mach_header_64));
	while (index++ < *((unsigned int*)(bin + HDR_NCMDS)) &&
			(void*)lc < bin_size + (void*)bin)
	{
		if (lc->cmd == (arch == 64 ? LC_SEGMENT_64 : LC_SEGMENT) && !(i = 0))
		{
			if ((rslt = check_segment((void*)lc, arch, size)))
				return (rslt);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (0);
}


void	mach_o(char *bin, size_t bin_size, char arch)
{
	uint64_t	tab;
	uint64_t	size;

	size = 0;
	if ((tab = get_secttab(bin, bin_size, arch, &size)) == 0)
		return ;
	if (tab + size >= bin_size)
		error(CORR_BIN);
	printf("size: %llu\n", size);
	printf("addr: %llu\n", tab);
	print(bin, tab, size);
	return ;
}
