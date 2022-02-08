#include "woody.h"

static int	remove_protection(Elf64_Ehdr *elf_hdr, Elf64_Phdr *hdata, char *binary)
{
	(void)elf_hdr;
	(void)binary;
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
	hdata->p_type = PT_LOAD;
	hdata->p_flags |= PF_W;
	hdata->p_flags |= PF_X;
	hdata->p_flags |= PF_R;
	return (0);
}

static int	set_binary(t_woody *woody)
{
	char	content[] = "\x50\x53\x51\x52\x56\x57\x54\x55\x41\x50\x41\x51\x41\x52\x41\x53\x41\x54\x41\x55\x41\x56\x41\x57\xb8\x01\x00\x00\x00\xbf\x01\x00\x00\x00\x68\x57\x4f\x4f\x44\x68\x2e\x2e\x2e\x2e\x48\x89\xe6\xba\x0e\x00\x00\x00\x0f\x05\x58\x58\xb8\x01\x00\x00\x00\xbf\x01\x00\x00\x00\x68\x2e\x0a\x00\x00\x68\x59\x2e\x2e\x2e\x48\x89\xe6\xba\x0e\x00\x00\x00\x0f\x05\x58\x58\x41\x5f\x41\x5e\x41\x5d\x41\x5c\x41\x5b\x41\x5a\x41\x59\x41\x58\x5d\x5c\x5f\x5e\x5a\x59\x5b\x58\xe9\x0d\x11\x11\x11";
	size_t content_len = 117;
	t_segments	lseg;

	init_segments(&lseg, woody->elf_hdr, woody->bindest);
	//display_segment_info(woody->elf_hdr, woody->bindest);
	remove_protection(woody->elf_hdr, lseg.hdata, woody->bindest);
	woody->key = keygen();
	ft_printf("key : '%lx'\n", woody->key);
	edit_segment_size_loop(woody, &lseg, content_len);
	add_to_end_segment(woody, &lseg, content, content_len);
	encrypt(woody, &lseg);
	//display_segment_info(woody->elf_hdr, woody->bindest);
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
