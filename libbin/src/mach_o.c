/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:55:49 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/22 15:04:12 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbin.h"
#include "stdio.h"

void		*get_symtab(char *bin, size_t bin_size, char arch)
{
	struct mach_header		*hdr;
	struct load_command		*lc;
	unsigned int			index;

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
