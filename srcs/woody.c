#include "woody.h"

static int	remove_protection(Elf64_Ehdr *elf_hdr, char *binary)
{
	Elf64_Shdr	*sh;
	Elf64_Phdr	*phdata;

	if (elf_hdr->e_type == ET_DYN)
		elf_hdr->e_type = (uint16_t)ET_EXEC;
	if (!(sh = get_section_by_name(elf_hdr, binary, ".data")))
		return (1);
	sh->sh_flags |= 1UL << SHF_EXECINSTR;
	if (!(phdata = get_segment_hdata(elf_hdr, binary)))
		return (2);
	phdata->p_flags |= 1UL << PF_W;
	return (0);
}

static int	set_binary(t_woody *woody)
{
	Elf64_Phdr	*phdata;

	if (!(phdata = get_segment_hdata(woody->elf_hdr, woody->binary)))
		return (1);
	add_to_end_segment(phdata, woody->binary, "lala");
	return (0);
}

int			ft_woody(t_woody *woody)
{
	display_elf_info(woody->elf_hdr);
	set_section(woody->elf_hdr, woody->binary);
	remove_protection(woody->elf_hdr, woody->binary);
	set_binary(woody);
	//chiffrement
	if ((woody->fd_dest = create_file("woody")) > -1)
		write_file(woody->fd_dest, woody->binary);
	return (0);
}
