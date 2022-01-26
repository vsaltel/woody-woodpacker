#include "woody.h"

void		display_segment_info(Elf64_Ehdr *elf_hdr, char *binary)
{
	Elf64_Phdr	*segment;
	int			i;

	i = -1;
	segment = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	while (++i < elf_hdr->e_phnum)
	{
		ft_printf("%d\tp_memsz %ld, p_filesz %ld, p_align %ld\n", i, segment[i].p_memsz, segment[i].p_filesz, segment[i].p_align);
		ft_printf("\tp_vaddr %ld, p_offset %ld\n", segment[i].p_vaddr, segment[i].p_offset);
		ft_printf("\tp_flags %c%c%c, p_type %d\n", (segment[i].p_flags & PF_R ? 'R' : ' '), (segment[i].p_flags & PF_W ? 'W' : ' '), (segment[i].p_flags & PF_X ? 'X' : ' '), segment[i].p_type);
	}
}

int			get_index_hdata(Elf64_Ehdr *elf_hdr, char *binary)
{
	/*
	Elf64_Phdr	*segment;
	int			i;

	i = -1;
	segment = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	while (++i < elf_hdr->e_phnum)
		if ((segment[i].p_flags & PF_R) && (segment[i].p_flags & PF_X))
				return (i);
	return (-1);
	*/
	Elf64_Phdr	*segment;
	int			i;
	int			y;

	y = 0;
	i = -1;
	segment = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	while (++i < elf_hdr->e_phnum)
		if ((segment[i].p_flags & PF_R) && (segment[i].p_flags & PF_W))
		{
				y = i;
				break ;
		}
	if (y != 0)
	{
		while (++y < elf_hdr->e_phnum)
		{
			ft_printf("act = %d, searched = %d\n", segment[y].p_type, PT_NOTE);
			if (segment[y].p_type == PT_NOTE)
			{
				ft_printf("here %d\n", y);
				i = y;
			}
		}
		return (i);
	}
	return (-1);
}

int			init_segments(t_segments *seg, Elf64_Ehdr *elf_hdr, char *binary)
{
	seg->begin = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	seg->hdata_index = get_index_hdata(elf_hdr, binary);
	seg->hdata = seg->begin + seg->hdata_index;
	seg->len = elf_hdr->e_phnum;
	return (0);
}

void		edit_segment_size_loop(t_woody *woody, t_segments *lseg, size_t len)
{
	Elf64_Phdr	*segment;
	//Elf64_Phdr	*tmp;
	//size_t		i;
	(void)woody;

	segment = lseg->hdata;

	ft_printf("p_memsz %ld, p_filesz %ld, p_align %ld\n", segment->p_memsz, segment->p_filesz, segment->p_align);
	ft_printf("p_vaddr %ld, p_offset %ld\n", segment->p_vaddr, segment->p_offset);
	ft_printf("p_flags %c%c%c\n", (segment->p_flags & PF_R ? 'R' : ' '), (segment->p_flags & PF_W ? 'W' : ' '), (segment->p_flags & PF_X ? 'X' : ' '));

	segment->p_memsz += len; 
	segment->p_filesz += len; 

	/*
	tmp = lseg->begin;
	i = lseg->hdata_index;
	while (++i < woody->elf_hdr->e_phnum)
		if (tmp[i].p_vaddr > segment->p_vaddr)
		{
			if ((unsigned char)woody->elf_hdr->e_ident[EI_OSABI] != ELFOSABI_FREEBSD)
				tmp[i].p_vaddr += len;
			else
				tmp[i].p_vaddr = 0;
			tmp[i].p_offset += len;
		}
	*/
}

int			add_to_end_segment(t_woody *woody, t_segments *lseg, char *content, size_t content_len)
{
	char	*tmp;
	//int		i;

	/*
	tmp = malloc(woody->len + content_len);
	ft_memcpy(tmp, woody->bindest, lseg->hdata->p_offset + lseg->tmp_filesz);
	i = lseg->hdata->p_offset + lseg->tmp_filesz;
	ft_memcpy(tmp + i, content, content_len);
	ft_printf("bntrypoint %d\n", woody->elf_hdr->e_entry);
	ft_printf("entrypoint %d\n", lseg->hdata->p_vaddr + lseg->tmp_filesz);
	i += content_len;
	ft_memcpy(tmp + i, woody->bindest + lseg->hdata->p_offset + lseg->tmp_filesz, woody->len - (lseg->hdata->p_offset + lseg->tmp_filesz));
	*/


	tmp = malloc(woody->len);
	ft_memcpy(tmp, woody->bindest, woody->len);
	ft_memcpy(tmp + lseg->hdata->p_offset + lseg->tmp_filesz, content, content_len);

	free(woody->bindest);
	woody->bindest = tmp;
	woody->elf_hdr = (Elf64_Ehdr *)woody->bindest;
	woody->len += content_len;
	woody->elf_hdr->e_entry = lseg->hdata->p_vaddr + lseg->tmp_filesz;	//entry point
	return (0);
}
