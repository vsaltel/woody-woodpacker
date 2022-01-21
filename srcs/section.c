#include "woody.h"

Elf64_Shdr	*get_section_by_name(Elf64_Ehdr *elf_hdr, char *binary, char *name)
{
	Elf64_Shdr			*section;
	Elf64_Shdr			*strtab;
	long unsigned int	i;

	if (!elf_hdr || !binary || !name)
		return (NULL);
	section = (Elf64_Shdr *)(binary + elf_hdr->e_shoff);
	strtab = &(section[elf_hdr->e_shstrndx]);
	i = -1;
	while (++i < elf_hdr->e_shnum)
		if (!strcmp(binary + strtab->sh_offset + section[i].sh_name, name))
			break ;
	if (i >= elf_hdr->e_shnum)
		return (NULL);
	return (&section[i]);
}

t_section	*get_data_section(t_section *dest, Elf64_Shdr *sh, char *binary)
{
	if (!sh || !dest)
		return (NULL);
	dest->data = binary + sh->sh_offset;
	dest->len = sh->sh_size;
	return (dest);
}

int			set_section(Elf64_Ehdr *elf_hdr, char *binary)
{
	Elf64_Shdr	*sh;

	if (!(sh = get_section_by_name(elf_hdr, binary, ".text")))
		return (1);
	ft_dprintf(2, "sdeb %x, sfin %x, add %x\n", sh->sh_offset, sh->sh_offset + sh->sh_size, sh->sh_addr);
	return (0);
}
