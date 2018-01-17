/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:19:32 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/17 16:21:59 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include "libbin.h"

# define MAGIC_ELF 0x464C457F

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
/*
enum e_type
{
	UNKNOW
};
*/
typedef struct s_data
{
	char		*name;
//	enum e_type	type;
	char		type;
	size_t		offset;
}				t_data;

typedef struct s_list
{
	t_data		data;
	struct s_list*		next;
}				t_list;

t_list	*mach_o(char *bin, size_t bin_size, char arch);
t_list	*fat_o(char *bin, size_t bin_size, char arch, char *name);
void	new_elem(t_list **head, char *name, char type, size_t offset);
void	free_list(t_list *list);
void	print(t_list *list, char arch);
void 	error (enum e_rror error) __attribute__((noreturn));
void	sort(t_list *head);

#endif
