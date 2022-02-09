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
	t_segments	lseg;

	init_segments(&lseg, woody->elf_hdr, woody->bindest);
	check_data_available(woody, &lseg);
	//display_segment_info(woody->elf_hdr, woody->bindest);
	remove_protection(woody->elf_hdr, lseg.hdata, woody->bindest);
	woody->key = keygen();
	ft_printf("key : '%lx'\n", woody->key);
	edit_segment_size_loop(woody, &lseg);
	add_to_end_segment(woody, &lseg);
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
	if ((woody->fd_dest = create_file("woody")) > -1)
		write_file(woody->fd_dest, woody->bindest, woody->len);
	free(woody->bindest);
	return (0);
}
