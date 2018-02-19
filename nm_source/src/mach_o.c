/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:28:16 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/19 17:44:43 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

#define NSECTS_64 (int)(&((struct segment_command_64*)(0x0))->nsects)
#define NSECTS_32 (int)(&((struct segment_command*)(0x0))->nsects)
#define SECTNAME_64 (int)(&((struct segment_command_64*)(0x0))->segname)
#define SECTNAME_32 (int)(&((struct segment_command*)(0x0))->segname)
#define HDR_NCMDS (int)(&((struct mach_header*)(0x0))->ncmds)

static char	*check_segment(void *addr, size_t *j, char arch, char n)
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
		if (n == (char)*j)
			return (arch == 64 ? sect_64->sectname : sect_32->sectname);
		sect_32 += 1;
		sect_64 += 1;
		i += 1;
		*j += 1;
	}
	return (NULL);
}

static char	*get_secttab(char *bin, size_t bin_size, char arch, char n)
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

static char	section_type(char *bin, size_t bin_size, char arch, char n)
{
	char *str;

	if ((str = get_secttab(bin, bin_size, arch, n)) == NULL)
		return ('S');
	if (ft_strcmp(str, "__text") == 0)
		return ('T');
	else if (ft_strcmp(str, "__bss") == 0)
		return ('B');
	else if (ft_strcmp(str, "__data") == 0)
		return ('D');
	return ('S');
}

static char	type(uint16_t sectype, char *bin, size_t bin_size, char arch)
{
	uint8_t	sec;
	uint8_t	type;
	char	ret;

	type = sectype;
	sec = sectype >> 8;
	if ((type & N_TYPE) == N_UNDF && sec == 0)
		ret = 'U';
	else if ((type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type & N_TYPE) == N_SECT)
		ret = section_type(bin, bin_size, arch, sec);
	else
		return ('?');
	return ((type & N_EXT) ? ret : ret + 32);
}

t_list		*mach_o(char *bin, size_t bin_size, char arch)
{
	size_t					i;
	struct symtab_command	*sym;
	struct nlist_64			*tab64;
	struct nlist			*tab32;
	t_list					*head;

	if ((sym = (struct symtab_command*)get_symtab(bin, bin_size, arch)) == NULL)
		return (NULL);
	i = -1;
	head = NULL;
	tab32 = (void*)bin + sym->symoff;
	tab64 = (void*)bin + sym->symoff;
	while (++i < sym->nsyms)
		if (arch == 64 && (tab64[i].n_type == 1 || tab64[i].n_type == 14
					|| tab64[i].n_type == 15))
			new_elem(&head, (void*)bin + sym->stroff + tab64[i].n_un.n_strx,
					type((uint16_t)((tab64[i].n_sect << 8) | tab64[i].n_type)
						, bin, bin_size, arch), tab64[i].n_value);
		else if (arch == 32 && (tab32[i].n_type == 1 || tab32[i].n_type == 14
					|| tab32[i].n_type == 15 || tab32[i].n_type == 0
					|| tab32[i].n_type == 3 || tab32[i].n_type == 30))
			new_elem(&head, (void*)bin + sym->stroff + tab32[i].n_un.n_strx,
					type((uint16_t)((tab32[i].n_sect << 8) | tab32[i].n_type)
						, bin, bin_size, arch), tab32[i].n_value);
	return (head);
}
