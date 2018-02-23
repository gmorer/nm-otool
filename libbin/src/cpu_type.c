/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:18:15 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/22 15:11:33 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbin.h"

static char	*another_cpu(cpu_type_t cpu)
{
	if (cpu == CPU_TYPE_POWERPC)
		return ("ppc");
	if (cpu == CPU_TYPE_POWERPC64)
		return ("ppc64");
	else
		return ("unknow cpu");
}

char		*get_cpu_type(cpu_type_t cpu)
{
	if (cpu == CPU_TYPE_MC680x0)
		return ("mc680");
	if (cpu == CPU_TYPE_I386)
		return ("i386");
	if (cpu == CPU_TYPE_X86)
		return ("x86");
	if (cpu == CPU_TYPE_X86_64)
		return ("x86_64");
	if (cpu == CPU_TYPE_MC98000)
		return ("mc98000");
	if (cpu == CPU_TYPE_HPPA)
		return ("hppa");
	if (cpu == CPU_TYPE_ARM)
		return ("arm");
	if (cpu == CPU_TYPE_ARM64)
		return ("arm64");
	if (cpu == CPU_TYPE_MC88000)
		return ("mc88000");
	if (cpu == CPU_TYPE_SPARC)
		return ("sparc");
	if (cpu == CPU_TYPE_I860)
		return ("I860");
	return (another_cpu(cpu));
}
