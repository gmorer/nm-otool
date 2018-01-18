/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:15:36 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/18 19:30:31 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbin.h"
#include <stdio.h>

static char	*reverse_endian(char *bin, size_t len)
{
	size_t	i;
	int32_t	*data;

	i = 0;
	len = len / 4;
	data = (void*)bin;
	printf("len: %zu\n", len);
	while (i < len)
	{
		data[i] = ((data[i] & 0xff000000) >> 24) |
			((data[i] & 0x00ff0000) >> 8) |
			((data[i] & 0x0000ff00) << 8) | (data[i] << 24);
		i += 1;
	}
	return (bin);
}

/*
** swap hdr for the number of struct.
** then swap (number of struct) * sizof(struct)
*/

static char	*swap_fat(char *bin, size_t size, int arch)
{
	reverse_endian(bin, 8);
	//printf("bin : %p\n", bin);
	//printf("len:%u\n", *(unsigned int*)(bin + 4));
	//printf("lennnnnnnnn: %zu\n", *(unsigned int*)(bin + 4) * (arch == 64 ?
	//				sizeof(struct fat_arch) : sizeof(struct fat_arch_64)));
	reverse_endian(bin + 8, *(unsigned int*)(bin + 4) * (arch == 64 ?
					sizeof(struct fat_arch) : sizeof(struct fat_arch_64)));
//	printf("%u\n", *(unsigned int*)bin);
	(void)size;
	(void)arch;
	return (bin);
}

static char *swap_mach_o(char *bin, size_t size, int arch)
{
	struct mach_header	*hdr;

	reverse_endian(bin, sizeof(struct mach_header));
	hdr = (struct mach_header*)bin;
	printf("size of all the load cmd: %u\n", hdr->sizeofcmds);
	if (arch == 32)
		reverse_endian(bin + sizeof(struct mach_header), hdr->sizeofcmds);
	if (arch == 64)
		reverse_endian(bin + sizeof(struct mach_header_64), hdr->sizeofcmds);
	return (bin);
}

char		*endian_auto_reverse(char *bin, size_t size)
{
	if (*(unsigned int*)bin == MH_CIGAM)
		return (swap_mach_o(bin, size, 32));
	else if (*(unsigned int*)bin == MH_CIGAM_64)
		return (swap_mach_o(bin, size, 64));
	else if (*(unsigned int*)bin == FAT_CIGAM)
		return (swap_fat(bin, size, 32));
	else if (*(unsigned int*)bin == FAT_CIGAM_64)
		return (swap_fat(bin, size, 64));

	return (bin);


}
