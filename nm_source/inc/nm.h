/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:19:32 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/19 17:21:30 by gmorer           ###   ########.fr       */
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

typedef struct			s_data
{
	char				*name;
	char				type;
	size_t				offset;
}						t_data;

typedef struct			s_list
{
	t_data				data;
	struct s_list		*next;
}						t_list;

t_list					*mach_o(char *bin, size_t bin_size, char arch);
t_list					*fat_o(char *bin, size_t bin_size, char arch,
		char *name);
int						arch_separator(char *bin, size_t bin_size, char *name);
void					new_elem(t_list **head, char *name, char type,
		size_t offset);
void					free_list(t_list *list);
void					print(t_list *list, char arch);
t_list					*sort(t_list *head);

#endif
