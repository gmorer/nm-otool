/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 11:51:33 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/17 12:58:03 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	new_elem(t_list **head, char *name, char type, size_t offset)
{
	t_list	*tmp;

	if (!(tmp = *head))
	{
		if (!(*head = malloc(sizeof(t_list))))
			error(MALLOC);
		(*head)->data.name = name;
		(*head)->data.type = type;
		(*head)->data.offset = offset;
		(*head)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = malloc(sizeof(t_list))))
		error(MALLOC);
	tmp->next->data.name = name;
	tmp->next->data.type = type;
	tmp->next->data.offset = offset;
	tmp->next->next = NULL;
	return ;
}

t_list	*join_list(t_list *lista, t_list *listb)
{
	if (!lista && !listb)
		return (NULL);
	else if (!lista || !listb)
		return (!lista ? listb : lista);
	while (lista->next)
		lista = lista->next;
	lista->next = listb;
	return (lista);
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}
