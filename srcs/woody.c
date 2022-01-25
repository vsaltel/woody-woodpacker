#include "woody.h"

static int	remove_protection(Elf64_Ehdr *elf_hdr, Elf64_Phdr *hdata, char *binary)
{
	/*
	Elf64_Shdr	*sh;

	if (elf_hdr->e_type == ET_DYN)
		elf_hdr->e_type = ET_EXEC;
	if (!(sh = get_section_by_name(elf_hdr, binary, ".data")))
		return (1);
	sh->sh_flags |= 1UL << SHF_EXECINSTR;
	*/
	if (!hdata)
		return (2);
	hdata->p_flags |= 1UL << PF_W;
	hdata->p_flags |= 1UL << PF_X;
	hdata->p_flags |= 1UL << PF_R;
	return (0);
}

static int	set_binary(t_woody *woody)
{
	const char exe[] = "\xb8\x01\x00\x00\x00\xbf\x01\x00\x00\x00\x68\x57\x4f\x4f\x44\x68\x2e\x2e\x2e\x2e\x48\x89\xe6\xba\x0e\x00\x00\x00\x0f\x05\xb8\x01\x00\x00\x00\xbf\x01\x00\x00\x00\x6a\x2e\x68\x59\x2e\x2e\x2e\x48\x89\xe6\xba\x0e\x00\x00\x00\x0f\x05\xb8\x3c\x00\x00\x00\xbf\x00\x00\x00\x00\x0f\x05";
	const size_t exe_len = 69;
	t_segments	lseg;

	init_segments(&lseg, woody->elf_hdr, woody->bindest);
	remove_protection(woody->elf_hdr, lseg.hdata, woody->bindest);
	lseg.tmp_filesz = lseg.hdata->p_filesz;
	lseg.tmp_memsz = lseg.hdata->p_memsz;
	//update_section_pos(woody, &lseg, exe_len);
	edit_segment_size_loop(woody, &lseg, exe_len);
	add_to_end_segment(woody, &lseg, (char *)exe, exe_len);
	//woody->elf_hdr->e_entry = lseg.hdata->p_offset;
	return (0);
}

int			ft_woody(t_woody *woody)
{
	woody->bindest = malloc(woody->len);
	woody->bindest = ft_memcpy(woody->bindest, woody->binary, woody->len);
	woody->elf_hdr = (Elf64_Ehdr *)woody->bindest;
	display_elf_info(woody->elf_hdr);
	set_binary(woody);
	//chiffrement
	if ((woody->fd_dest = create_file("woody")) > -1)
		write_file(woody->fd_dest, woody->bindest, woody->len);
	free(woody->bindest);
	return (0);
}
