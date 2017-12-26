#include "nm.h"
#include <stdio.h>

static long long unsigned get_symtab(char *bin, void *shoff, size_t size,
		int index)
{
	Elf32_Shdr	*tshd;
	Elf64_Shdr	*sshd;

	printf("phoff: %p, bin: %p\n", shoff, bin);
	while (index)
	{
		if (bin[4] == 1) // 32 bits
		{
			tshd = (Elf32_Shdr*)shoff;
			if (tshd->sh_type == SHT_SYMTAB)
				return (tshd->sh_offset);
		}
		if (bin[4] == 2) // 64 bits
		{
			sshd = (Elf64_Shdr*)shoff;
			if (sshd->sh_type == SHT_SYMTAB)
				return (sshd->sh_offset);
		}
		shoff += size;
		index--;
	}
	return (0);
}

void	print_symtab(Elf64_Sym *tab)
{
	int i;

	i = 0;
	while(i < 50)
	{
		printf("section type:%d\n", (((&tab[i])->st_info)&0xf));
		i++;
	}
}

int elf_nm(char *bin, int arch)
{
	Elf32_Ehdr	*t_hdr;
	Elf64_Ehdr	*s_hdr;
	void		*phdr;
	//void		*shoff;

	if (arch == 32)
	{
		t_hdr = (Elf32_Ehdr*)bin;
		phdr = (Elf32_Phdr*)(t_hdr->e_phoff + (void*)bin);
		printf("eshoff: %d\n", t_hdr->e_shoff);
		get_symtab(bin, t_hdr->e_shoff + (void*)0, t_hdr->e_shentsize, t_hdr->e_shnum);
	}
	else if (arch == 64)
	{
		s_hdr = (Elf64_Ehdr*)bin;
		phdr = (Elf64_Phdr*)(s_hdr->e_phoff + (void*)bin);
		printf("eshoff: %p\n", (void*)s_hdr->e_shoff);
		print_symtab((Elf64_Sym*)get_symtab(bin, s_hdr->e_shoff + bin, s_hdr->e_shentsize, s_hdr->e_shnum));
	}
	//printf("last address: %p\n", shoff);
	(void)phdr;
	return (1);
}
