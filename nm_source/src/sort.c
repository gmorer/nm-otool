/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:52:06 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/18 19:28:10 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	if (!s1)
	{
		if (!s2)
			return (0);
		else
			return (1);
	}
	else if (!s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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

void		sort(t_list *head)
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
}
