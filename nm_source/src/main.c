/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:20:16 by gmorer            #+#    #+#             */
/*   Updated: 2017/12/14 19:14:26 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

void error(enum e_rror error)
{
	write(2, "nm: ", 4);
	if (error == ARG)
		write(2, "usage: nm [FILE]\n", 17);
	if (error == OPEN)
		write(2, "cant open the file\n", 19);
	if (error == CLOSE)
		write(2, "cant close the file\n", 20);
	if (error == CLOSE)
		write(2, "error during fstat\n", 19);
	if (error == MMAP)
		write(2, "error during mmap\n", 18);
	if (error == ARCH_ERR)
		write(2, "error: unknow architecture\n", 27);
	exit(error + 1);
}

static int	arch_separator(char *bin)
{
	if (*(int*)bin == MAGIC_ELF)
	{
		if (bin[4] == 1 || bin[4] == 2)
			elf_nm(bin, bin[4] == 1 ? 32 : 64);
		else
			error(ARCH_ERR);
	}
	else
		error(ARCH_ERR);
	return (1);
}

int main(int ac, char **av)
{
	int			fd;
	struct stat	metadata;
	void		*bin;

	if (ac < 2)
		error(ARG);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		error(OPEN);
	if (fstat(fd, &metadata) == -1)
		error(FSTAT);
	if ((bin = mmap(0, (size_t)metadata.st_size, PROT_READ, MAP_PRIVATE,
					fd, 0)) == MAP_FAILED)
		error(MMAP);
	/* code here */
	arch_separator(bin);


	/* end of the code */
	if (munmap(bin, (size_t)metadata.st_size) == -1)
		error(MMAP);
	if (close(fd) == -1)
		error(CLOSE);
	return (1);
}
