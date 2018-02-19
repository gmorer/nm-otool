/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 13:16:04 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/19 15:10:31 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbin.h"

void	 ft_putstr(char *str)
{
	size_t i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	return ;
}

int		ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	if (str1 == NULL && str2 == NULL)
		return (0);
	if (str1 == NULL || str2 == NULL)
		return (str1 == NULL ? -1 : 1);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}
