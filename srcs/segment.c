#include "woody.h"

Elf64_Phdr	*get_segment_hdata(Elf64_Ehdr *elf_hdr, char *binary)
{
	Elf64_Phdr	*segment;
	int			i;

	i = -1;
	segment = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	while (++i < elf_hdr->e_phnum)
		if ((segment[i].p_flags & PF_R) && (segment[i].p_flags & PF_X))
				return (&segment[i]);
	return (NULL);
}

int			add_to_end_segment(Elf64_Phdr *phdr, char *binary, char *content)
{
	char	*end;

	end = binary + phdr->p_offset + phdr->p_filesz;
	ft_dprintf(2, "filesz %u, memsz %u\n", phdr->p_filesz, phdr->p_memsz);
	(void)end;
	(void)content;
	//set p_vaddr
	//set p_offset des segments suivant
	//set p_filez
	//set p_memsz
	//set p_align
	return (0);
}
