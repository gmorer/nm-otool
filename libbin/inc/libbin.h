/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:12:32 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/18 15:07:15 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBIN_H
# define LIBBIN_H

# include <mach/machine.h>
# include <unistd.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>


# define L_ENDIAN 0
# define B_ENDIAN 1

char		*endian_auto_reverse(char *bin, size_t len);
char		*get_cpu_type(cpu_type_t cpu);

#endif
