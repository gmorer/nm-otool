/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:20:16 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/19 15:14:09 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

void		error(enum e_rror error)
{
	write(2, "nm: ", 4);
	if (error == ARG)
		write(2, "usage: nm [FILE]\n", 17);
	else if (error == OPEN)
		write(2, "cant open the file\n", 19);
	else if (error == MALLOC)
		write(2, "error: malloc error\n", 19);
	else if (error == CLOSE)
		write(2, "cant close the file\n", 20);
	else if (error == FSTAT)
		write(2, "error during fstat\n", 19);
	else if (error == MMAP)
		write(2, "error during mmap\n", 18);
	else if (error == ARCH_ERR)
		write(2, "error: unknow architecture\n", 27);
	else if (error == CORR_BIN)
		write(2, "error: corrupted file\n", 22);
	exit(error + 1);
}

int	arch_separator(char *bin, size_t bin_size, char *name)
{
	t_list		*list;
	char		arch;

	bin = endian_auto_reverse(bin, bin_size);
	if (*(unsigned int*)bin == MH_MAGIC_64)
		list = mach_o(bin, bin_size,
				(arch = 64));
	else if (*(unsigned int*)bin == MH_MAGIC)
		list = mach_o(bin, bin_size,
				(arch = 32));
	else if (*(unsigned int*)bin == FAT_MAGIC_64)
		list = fat_o(bin, bin_size,
				(arch = 64), name);
	else if (*(unsigned int*)bin == FAT_MAGIC)
		list = fat_o(bin, bin_size,
				(arch = 32), name);
	else
	{
		printf("%u\n", *(unsigned int*)bin);
		error(ARCH_ERR);
	}
	sort(list);
	print(list, arch);
	free_list(list);
	return (1);
}

static int	loop(char *file)
{
	int			fd;
	struct stat	metadata;
	void		*bin;

	if ((fd = open(file, O_RDONLY)) == -1)
		error(OPEN);
	if (fstat(fd, &metadata) == -1)
		error(FSTAT);
	if ((bin = mmap(0, (size_t)metadata.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE,
					fd, 0)) == MAP_FAILED)
		error(MMAP);
	arch_separator(bin, metadata.st_size, file);
	if (munmap(bin, (size_t)metadata.st_size) == -1)
		error(MMAP);
	if (close(fd) == -1)
		error(CLOSE);
	return (1);
}

int			main(int ac, char **av)
{
	if (ac < 2)
		error(ARG);
	av += 1;
	if (ac > 2)
		while (*av)
		{
			write(1, "\n", 1);
			ft_putstr(*av);
			write(1, ":\n", 2);
			loop(*av);
			av += 1;
		}
	else
		loop(av[1]);
	return (1);
}
