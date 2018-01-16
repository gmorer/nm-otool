/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:28:16 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/16 12:57:53 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

static void	*get_symtab(char *bin, size_t bin_size, char arch)
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
	if (index > hdr->ncmds)
		return (NULL);
	return ((void*)lc);
}

t_list		*mach_o(char *bin, size_t bin_size, char arch)
{
	size_t					i;
	struct symtab_command	*sym;
	struct nlist_64			*array64;
	struct nlist			*array32;
	t_list					*head;

	if ((sym = (struct symtab_command*)get_symtab(bin, bin_size, arch)) == NULL)
		return (NULL);
	i = -1;
	head = NULL;
	array32 = (void*)bin + sym->symoff;
	array64 = (void*)bin + sym->symoff;
	while (++i < sym->nsyms)
		if (arch == 64)
			new_elem(&head, (void*)bin + sym->stroff + array64[i].n_un.n_strx,
				array64[i].n_sect == 8 ? 8 :
				array64[i].n_type, array64[i].n_value);
		else
			new_elem(&head, (void*)bin + sym->stroff + array32[i].n_un.n_strx,
				array32[i].n_sect == 8 ? 8 :
				array32[i].n_type, array32[i].n_value);
	return (head);
}
