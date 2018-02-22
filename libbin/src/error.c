/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:09:32 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/22 13:45:39 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbin.h"

void		error(enum e_rror error)
{
	if (error == ARG)
		write(2, "usage: nm [FILE]\n", 17);
	else if (error == OPEN)
		write(2, "cant open the file\n", 19);
	else if (error == MALLOC)
		write(2, "error: malloc error\n", 19);
	else if (error == CLOSE)
		write(2, "cant close the file\n", 20);
	else if (error == FSTAT)
		write(2, "error during fstat\n", 19);
	else if (error == MMAP)
		write(2, "error during mmap\n", 18);
	else if (error == ARCH_ERR)
		write(2, "error: unknow architecture\n", 27);
	else if (error == CORR_BIN)
		write(2, "error: corrupted file\n", 22);
	exit(error + 1);
}
