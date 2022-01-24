#include "woody.h"

int			get_index_hdata(Elf64_Ehdr *elf_hdr, char *binary)
{
	Elf64_Phdr	*segment;
	int			i;

	i = -1;
	segment = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	while (++i < elf_hdr->e_phnum)
		if ((segment[i].p_flags & PF_R) && (segment[i].p_flags & PF_X))
				return (i);
	return (-1);
}

int			init_segments(t_segments *seg, Elf64_Ehdr *elf_hdr, char *binary)
{
	seg->begin = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	seg->hdata_index = get_index_hdata(elf_hdr, binary);
	seg->hdata = &seg->begin[seg->hdata_index];
	seg->len = elf_hdr->e_phnum;
	return (0);
}

int			add_to_end_segment(t_woody *woody, Elf64_Phdr *phdr, char *content, size_t seglen, size_t content_len)
{
	char	*tmp;
	int		i;

	tmp = malloc(woody->len + content_len);
	ft_memcpy(tmp, woody->bindest, phdr->p_offset + seglen);
	i = phdr->p_offset + seglen;
	ft_memcpy(tmp + i, content, content_len);
	i += content_len;
	ft_memcpy(tmp + i, woody->bindest + phdr->p_offset + seglen, woody->len - (phdr->p_offset + seglen));
	free(woody->bindest);
	woody->bindest = tmp;
	woody->len += content_len;
	return (0);
}

void		edit_segment_size_loop(t_woody *woody, t_segments *lseg, size_t len)
{
	Elf64_Phdr	*segment;
	size_t		i;

	segment = lseg->hdata;
	ft_dprintf(2, "vaddr %u, offset %u\n", segment->p_vaddr, segment->p_offset);
	ft_dprintf(2, "filesz %u, memsz %u\n", segment->p_filesz, segment->p_memsz);
	ft_dprintf(2, "align %u\n", segment->p_align);

	segment->p_memsz += len; 
	segment->p_filesz += len; 
	i = lseg->hdata_index;
	while (++i < lseg->len)
	{
		if ((unsigned char)woody->elf_hdr->e_ident[EI_OSABI] != ELFOSABI_FREEBSD)
			segment[i].p_vaddr += len;
		else
			segment[i].p_vaddr = 0;
		segment->p_offset += len;
		segment->p_align += len;
	}
}
