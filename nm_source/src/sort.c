/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:52:06 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/19 17:20:53 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	is_sorted(t_list *list)
{
	while (list && list->next)
	{
		if (ft_strcmp(list->data.name, list->next->data.name) > 0)
			return (0);
		list = list->next;
	}
	return (1);
}

t_list		*sort(t_list *head)
{
	t_data	tmp;
	t_list	*list;

	while (head && !is_sorted(head))
	{
		list = head;
		while (list->next)
		{
			if (ft_strcmp(list->data.name, list->next->data.name) > 0)
			{
				tmp = list->data;
				list->data = list->next->data;
				list->next->data = tmp;
			}
			list = list->next;
		}
	}
	return (head);
}
