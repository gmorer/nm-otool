/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:12:32 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/19 15:11:02 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBIN_H
# define LIBBIN_H

# include <unistd.h>
# include <stdlib.h>
# include <mach/machine.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>


# define L_ENDIAN 0
# define B_ENDIAN 1

enum e_rror
{
	ARG = 1,
	OPEN,
	CLOSE,
	FSTAT,
	MMAP,
	MALLOC,
	ARCH_ERR,
	CORR_BIN
};

char		*endian_auto_reverse(char *bin, size_t len);
char		*get_cpu_type(cpu_type_t cpu);
void		*get_symtab(char *bin, size_t bin_size, char arch);
void		error(enum e_rror error) __attribute__((noreturn));
int			ft_strcmp(char *str1, char *str2);
void		ft_putstr(char *str);

#endif
