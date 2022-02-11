#include "woody.h"

static int			check_segment(t_woody *woody, Elf64_Ehdr *hdr, Elf64_Phdr *seg, char *binary)
{
	int			i;

	if (!seg || !hdr)
		return (102);
	i = -1;
	while (++i < hdr->e_phnum)
	{
		if ((char *)(seg + i) > binary + woody->len)
			return (103);
		if (((char *)(seg + i) + sizeof(Elf64_Phdr)) > (binary + woody->len))
			return (104);
		if ((seg + i)->p_offset > woody->len)
			return (105);
		if (((seg + i)->p_offset + (seg + i)->p_filesz) > woody->len)
			return (106);
	}
	return (0);
}

static int			check_elf_hdr(t_woody *woody, Elf64_Ehdr *hdr)
{
	if (!hdr)
		return (100);
	if (sizeof(Elf64_Ehdr) > woody->len)
		return (101);
	return (0);
}

int		check_file(t_woody *woody)
{
	Elf64_Phdr	*seg_hdr;
	Elf64_Ehdr	*elf_hdr;
	int			ret;

	ret = 0;
	elf_hdr = (Elf64_Ehdr *)(woody->binary);
	if ((ret = check_elf_hdr(woody, elf_hdr)))
	{
		ft_dprintf(2, "woody-woodpacker: Invalid file\n");
		return (ret);
	}
	if ((ret = check_elf(woody->elf_hdr, woody->filename)))	
		return (ret);
	seg_hdr = (Elf64_Phdr *)(woody->binary + woody->elf_hdr->e_phoff);
	if ((ret = check_segment(woody, elf_hdr, seg_hdr, woody->binary)))
	{
		ft_dprintf(2, "woody-woodpacker: Invalid file\n");
		return (ret);
	}
	return (0);	
}
