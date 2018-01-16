/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:28:16 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/16 11:11:06 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

static void	*get_symtab(char *bin, size_t bin_size)
{
	struct mach_header_64	*hdr;
	struct load_command		*lc;
	unsigned int			index;

	hdr = (struct mach_header_64*)bin;
	index = 0;
	lc = (void*)bin + sizeof(struct mach_header_64);
	while (index < hdr->ncmds && (void*)lc < bin_size + (void*)bin)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			break;
		}
		lc = (void*)lc + lc->cmdsize;
		index++;
	}
	if ((void*)lc > bin_size + (void*)bin)
		error(CORR_BIN);
	if (index > hdr->ncmds)
		return (NULL);
	return ((void*)lc);
}

static void	new_elem(struct nlist_64 element, char *stringtable, t_list **head)
{
	t_list	*tmp;

	if (!(tmp = *head))
	{
		if ((*head = malloc(sizeof(t_list))) == NULL)
			error(MALLOC);
		(*head)->data.name = stringtable + element.n_un.n_strx;
		(*head)->data.type = element.n_sect == 8 ? 8 : element.n_type;
		(*head)->data.offset = element.n_value;
		(*head)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	if ((tmp->next = malloc(sizeof(t_list))) == NULL)
		error(MALLOC);
	tmp->next->data.name = stringtable + element.n_un.n_strx;
	tmp->next->data.type = element.n_sect == 8 ? 8 : element.n_type;
	tmp->next->data.offset = element.n_value;
	tmp->next->next = NULL;
	return ;
}

t_list	*mach_o(char *bin, size_t bin_size)
{
	unsigned int			i;
	struct symtab_command	*sym;
	struct nlist_64			*array;
	char					*stringtable;
	t_list					*head;

	if ((sym = (struct symtab_command*)get_symtab(bin, bin_size)) == NULL)
		return (NULL);
	i = 0;
	head = NULL;
	array = (void*) bin + sym->symoff;
	stringtable = (void*)bin + sym->stroff;
	while (i < sym->nsyms)
	{
		new_elem(array[i], stringtable, &head);
		i++;
	}
	return (head);
}
