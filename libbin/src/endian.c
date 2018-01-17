/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:15:36 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/17 16:16:24 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbin.h"

char		*reverse_endian(char *bin, size_t len)
{
	size_t	i;
	int32_t	*data;

	i = 0;
	len = len / 4;
	data = (void*)bin;
	while (i < len)
	{
		data[i] = ((data[i] & 0xff000000) >> 24) |
			((data[i] & 0x00ff0000) >> 8) |
			((data[i] & 0x0000ff00) << 8) | (data[i] << 24);
		i += 1;
	}
	return (bin);
}
