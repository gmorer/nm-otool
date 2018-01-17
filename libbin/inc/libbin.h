/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:12:32 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/17 16:17:52 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBIN_H
# define LIBBIN_H

# include <mach/machine.h>
# include <unistd.h>

char		*reverse_endian(char *bin, size_t len);
char		*get_cpu_type(cpu_type_t cpu);

#endif
