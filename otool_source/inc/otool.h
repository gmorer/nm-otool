/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:21:20 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/22 15:02:26 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include "libbin.h"

typedef struct	s_section
{
	uint64_t	addr;
	uint64_t	offset;
	uint64_t	size;
}				t_section;

void			mach_o(char *bin, size_t bin_size, char arch);
void			fat_o(char *bin, size_t bin_size, char arch, char *name);
void			print(char *bin, t_section sect, char arch);
int				arch_separator(char *bin, size_t bin_size, char *name);

#endif
