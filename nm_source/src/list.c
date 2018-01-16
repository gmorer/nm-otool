/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 11:51:33 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/16 12:28:43 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	new_elem(t_list **head, char *name, char type, size_t offset)
{
	t_list	*tmp;

	if (!(tmp = *head))
	{
		if ((*head = malloc(sizeof(t_list))) == NULL)
			error(MALLOC);
		(*head)->data.name = name;
		(*head)->data.type = type;
		(*head)->data.offset = offset;
		(*head)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	if ((tmp->next = malloc(sizeof(t_list))) == NULL)
		error(MALLOC);
	tmp->next->data.name = name;
	tmp->next->data.type = type;
	tmp->next->data.offset = offset;
	tmp->next->next = NULL;
	return ;
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
