/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:28:16 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/23 12:06:55 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

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
	//printf("symoff: %u, arch: %c, nsyms: %u\n",sym->symoff, arch, sym->nsyms);
	while (++i < sym->nsyms)
		if (arch == 64 && (array64[i].n_type == 1 || array64[i].n_type == 14
						 || array64[i].n_type == 15))
		{
		//	printf("type: %d, sect: %d, dec: %d, value: %llu, name: %s\n",
		//			array64[i].n_type, array64[i].n_sect, array64[i].n_desc,
		//			array64[i].n_value, (void*)bin + sym->stroff + array64[i].n_un.n_strx);
			new_elem(&head, (void*)bin + sym->stroff + array64[i].n_un.n_strx,
				array64[i].n_sect == 8 ? 8 :
				array64[i].n_type, array64[i].n_value);
		}
		else if (arch == 32 && (array32[i].n_type == 1 || array32[i].n_type == 14 || array32[i].n_type == 15 ||
							  array32[i].n_type == 0 || array32[i].n_type == 3 || array32[i].n_type == 30))
		{
	//		printf("type: %d, sect: %d, dec: %d, value: %d, name: %s\n",
	//				array32[i].n_type, array32[i].n_sect, array32[i].n_desc,
	//				array32[i].n_value, (void*)bin + sym->stroff + array32[i].n_un.n_strx);
			new_elem(&head, (void*)bin + sym->stroff + array32[i].n_un.n_strx,
				array32[i].n_sect == 8 ? 8 :
				array32[i].n_type, array32[i].n_value);
		}
	return (head);
}
