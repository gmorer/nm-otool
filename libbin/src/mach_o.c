/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:55:49 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/16 19:36:19 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbin.h"
#include "stdio.h"

#define NSECTS_64 (int)(&((struct segment_command_64*)(0x0))->nsects)
#define NSECTS_32 (int)(&((struct segment_command*)(0x0))->nsects)
#define SECTNAME_64 (int)(&((struct segment_command_64*)(0x0))->segname)
#define SECTNAME_32 (int)(&((struct segment_command*)(0x0))->segname)
#define HDR_NCMDS (int)(&((struct mach_header*)(0x0))->ncmds)

char		*get_secttab(char *bin, size_t bin_size, char arch, char n)
{
	struct load_command		*lc;
	struct section_64		*sect;
	unsigned int			index;
	size_t					i;
	size_t					j;

	index = 0;
	j = 0;
	lc = (void*)bin + (arch == 32 ? sizeof(struct mach_header) :
			sizeof(struct mach_header_64));
	while (index++ < *((unsigned int*)(bin + HDR_NCMDS)) &&
			(void*)lc < bin_size + (void*)bin)
	{
		if (lc->cmd == (arch == 64 ? LC_SEGMENT_64 : LC_SEGMENT) && !(i = 0))
		{
			sect = (void*)((void*)lc + (arch == 64 ? sizeof(struct segment_command_64) : sizeof(struct segment_command)));
			while (i < *((unsigned int*)((void*)lc +
							(arch == 64 ? NSECTS_64 : NSECTS_32))))
			{
				if (n == j)
					return (sect->sectname);//TODO sect isnt 32/64
				printf("section number: %zu -> %s\n", j, sect->sectname);
				sect += 1;
				i += 1;
				j += 1;
			}
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (NULL);
}

void		*get_symtab(char *bin, size_t bin_size, char arch)
{
	struct mach_header		*hdr;
	struct load_command		*lc;
	unsigned int			index;

	get_secttab(bin, bin_size, arch);
	hdr = (struct mach_header*)bin;
	index = 0;
	lc = (void*)bin + (arch == 32 ? sizeof(struct mach_header) :
			sizeof(struct mach_header_64));
	while (index < hdr->ncmds && (void*)lc < bin_size + (void*)bin)
	{
		if (lc->cmd == LC_SYMTAB)
			break ;
		lc = (void*)lc + lc->cmdsize;
		index++;
	}
	if ((void*)lc > bin_size + (void*)bin)
		error(CORR_BIN);
	if (index == hdr->ncmds)
	{
		return (NULL);
	}
	return ((void*)lc);
}
