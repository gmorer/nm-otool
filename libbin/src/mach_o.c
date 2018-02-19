/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:55:49 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/19 11:13:01 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbin.h"
#include "stdio.h"

/*
#define NSECTS_64 (int)(&((struct segment_command_64*)(0x0))->nsects)
#define NSECTS_32 (int)(&((struct segment_command*)(0x0))->nsects)
#define SECTNAME_64 (int)(&((struct segment_command_64*)(0x0))->segname)
#define SECTNAME_32 (int)(&((struct segment_command*)(0x0))->segname)
#define HDR_NCMDS (int)(&((struct mach_header*)(0x0))->ncmds)

char		*check_segment(void *addr, size_t *j, char arch, char n)
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
		if (n == *j)
			return (arch == 64 ? sect_64->sectname : sect_32->sectname);
		sect_32 += 1;
		sect_64 += 1;
		i += 1;
		*j += 1;
	}
	return (NULL);
}

char		*get_secttab(char *bin, size_t bin_size, char arch, char n)
{
	struct load_command		*lc;
	unsigned int			index;
	size_t					i;
	char					*rslt;
	size_t					j;

	index = 0;
	j = 1;
	lc = (void*)bin + (arch == 32 ? sizeof(struct mach_header) :
			sizeof(struct mach_header_64));
	while (index++ < *((unsigned int*)(bin + HDR_NCMDS)) &&
			(void*)lc < bin_size + (void*)bin)
	{
		if (lc->cmd == (arch == 64 ? LC_SEGMENT_64 : LC_SEGMENT) && !(i = 0))
		{
			if ((rslt = check_segment((void*)lc, &j, arch, n)))
				return (rslt);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (NULL);
}
*/
void		*get_symtab(char *bin, size_t bin_size, char arch)
{
	struct mach_header		*hdr;
	struct load_command		*lc;
	unsigned int			index;

//	get_secttab(bin, bin_size, arch, 99);
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
