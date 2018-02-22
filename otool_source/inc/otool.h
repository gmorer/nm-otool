/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:21:20 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/22 13:24:56 by gmorer           ###   ########.fr       */
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

void		mach_o(char *bin, size_t bin_size, char arch);
void		fat_o(char *bin, size_t bin_size, char arch, char *name);
void    	print(char *bin, uint64_t tab, uint64_t size, char arch);
int			arch_separator(char *bin, size_t bin_size, char *name);

#endif
