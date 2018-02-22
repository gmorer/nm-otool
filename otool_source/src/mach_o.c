/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:19:58 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/22 15:02:13 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

#define NSECTS_64 (int)(&((struct segment_command_64*)(0x0))->nsects)
#define NSECTS_32 (int)(&((struct segment_command*)(0x0))->nsects)
#define HDR_NCMDS (int)(&((struct mach_header*)(0x0))->ncmds)

static uint64_t	check_segment(void *addr, char arch, t_section *sect)
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
		if (!ft_strcmp(arch == 64 ? sect_64->sectname :
					sect_32->sectname, "__text"))
		{
			(*sect).size = arch == 64 ? sect_64->size : sect_32->size;
			(*sect).addr = arch == 64 ? sect_64->addr : sect_32->addr;
			(*sect).offset = arch == 64 ? sect_64->offset : sect_32->offset;
			return (1);
		}
		sect_32 += 1;
		sect_64 += 1;
		i += 1;
	}
	return (0);
}

static uint64_t	get_secttab(char *bin, size_t bin_size,
		char arch, t_section *sect)
{
	struct load_command		*lc;
	unsigned int			index;
	size_t					i;

	index = 0;
	lc = (void*)bin + (arch == 32 ? sizeof(struct mach_header) :
			sizeof(struct mach_header_64));
	while (index++ < *((unsigned int*)(bin + HDR_NCMDS)) &&
			(void*)lc < bin_size + (void*)bin)
	{
		if (lc->cmd == (arch == 64 ? LC_SEGMENT_64 : LC_SEGMENT) && !(i = 0))
		{
			if (check_segment((void*)lc, arch, sect))
				return (1);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (0);
}

void			mach_o(char *bin, size_t bin_size, char arch)
{
	uint64_t	tab;
	uint64_t	size;
	t_section	sect;

	size = 0;
	sect.addr = 0;
	sect.size = 0;
	sect.offset = 0;
	if ((tab = get_secttab(bin, bin_size, arch, &sect)) == 0)
		return ;
	print(bin, sect, arch);
	return ;
}
