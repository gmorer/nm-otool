/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:19:32 by gmorer            #+#    #+#             */
/*   Updated: 2017/12/14 18:58:31 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define MAGIC_ELF 0x464C457F

enum e_rror
{
	ARG = 1,
	OPEN,
	CLOSE,
	FSTAT,
	MMAP
};

void  error (enum e_rror error) __attribute__((noreturn));

#endif
