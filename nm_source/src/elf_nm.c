#include "nm.h"
#include <stdio.h>

void	print_phdrtype(unsigned int *type)
{
	if (*type == PT_NULL)
		write(1, "NULL\n", 5);
	else if (*type == PT_LOAD)
		write(1, "LOAD\n", 5);
	else if (*type == PT_DYNAMIC)
		write(1, "DYNAMIC\n", 8);
	else if (*type == PT_INTERP)
		write(1, "INTERP\n", 7);
	else if (*type == PT_NOTE)
		write(1, "NULL\n", 5);
	else if (*type == PT_SHLIB)
		write(1, "NULL\n", 5);
	else if (*type == PT_PHDR)
		write(1, "NULL\n", 5);
	else if (*type == PT_TLS)
		write(1, "NULL\n", 5);
	else if (*type == PT_LOOS)
		write(1, "NULL\n", 5);
	else if (*type == PT_HIOS)
		write(1, "NULL\n", 5);
	else if (*type == PT_LOPROC)
		write(1, "NULL\n", 5);
	else if (*type == PT_HIPROC)
		write(1, "NULL\n", 5);
	else if (*type == PT_GNU_EH_FRAME)
		write(1, "NULL\n", 5);
	else
		write(1, "unknow type\n", 12);
}


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

int elf_nm(char *bin, int arch)
{
	Elf32_Ehdr	*t_hdr;
	Elf64_Ehdr	*s_hdr;
	void		*phdr;
	void		*shoff;

	if (arch == 32)
	{
		t_hdr = (Elf32_Ehdr*)bin;
		phdr = (Elf32_Phdr*)(t_hdr->e_phoff + (void*)bin);
		printf("eshoff: %d\n", t_hdr->e_shoff);
		get_symtab(bin, shoff, t_hdr->e_shentsize, t_hdr->e_shnum);
	}
	else if (arch == 64)
	{
		s_hdr = (Elf64_Ehdr*)bin;
		phdr = (Elf64_Phdr*)(s_hdr->e_phoff + (void*)bin);
		printf("eshoff: %p\n", (void*)s_hdr->e_shoff);
		get_symtab(bin, s_hdr->e_shoff + bin, s_hdr->e_shentsize, s_hdr->e_shnum);
	}
	printf("last address: %p\n", shoff);
	(void)phdr;
	return (1);
}
