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
	Elf64_Phdr	*segment;
	int			i;

	i = -1;
	segment = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	while (++i < elf_hdr->e_phnum)
		if ((segment[i].p_flags & PF_R) && (segment[i].p_flags & PF_X))
				return (i);
	return (-1);
	/*
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
	*/
}

int			init_segments(t_segments *seg, Elf64_Ehdr *elf_hdr, char *binary)
{
	seg->begin = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	seg->hdata_index = get_index_hdata(elf_hdr, binary);
	seg->hdata = seg->begin + seg->hdata_index;
	seg->code_len = seg->hdata->p_filesz;
	seg->seg_len = elf_hdr->e_phnum;
	return (0);
}

int			get_lastest_segment(Elf64_Ehdr *elf_hdr, Elf64_Phdr *tmp)
{
	size_t		i;
	size_t		y;
	size_t		len_tmp;

	i = -1;
	y = 0;
	len_tmp = 0;
	while (++i < elf_hdr->e_phnum)
		if ((tmp[i].p_offset + tmp[i].p_filesz) > len_tmp)
		{
			y = i;
			len_tmp = (tmp[i].p_vaddr + tmp[i].p_filesz);
		}
	return (y);
}

void		edit_segment_size_loop(t_woody *woody, t_segments *lseg, size_t len)
{
	//Elf64_Phdr	*tmp;
	//size_t		y;
	(void)woody;

	/*
	ft_printf("p_memsz %ld, p_filesz %ld, p_align %ld\n", lseg->hdata->p_memsz, lseg->hdata->p_filesz, lseg->hdata->p_align);
	ft_printf("p_vaddr %ld, p_offset %ld\n", lseg->hdata->p_vaddr, lseg->hdata->p_offset);
	ft_printf("p_flags %c%c%c\n", (lseg->hdata->p_flags & PF_R ? 'R' : ' '), (lseg->hdata->p_flags & PF_W ? 'W' : ' '), (lseg->hdata->p_flags & PF_X ? 'X' : ' '));

	tmp = lseg->begin;
	y = get_lastest_segment(woody->elf_hdr, tmp);
	ft_printf("lastest : %ld, %ld, %ld\n", woody->elf_hdr->e_shoff, tmp[y].p_offset + tmp[y].p_filesz, tmp[y].p_offset);
	for (size_t i = tmp[y].p_offset + tmp[y].p_filesz; i < woody->elf_hdr->e_shoff; i++) {
        ft_printf(" %2x", woody->bindest[i]);
    }	

	lseg->hdata->p_align = 1;
	lseg->hdata->p_vaddr = tmp[y].p_vaddr + ((tmp[y].p_memsz / tmp[y].p_align + ((tmp[y].p_memsz % tmp[y].p_align != 0) ? 1 : 0)) * tmp[y].p_align);
	lseg->hdata->p_offset = tmp[y].p_offset + ((tmp[y].p_filesz / tmp[y].p_align + ((tmp[y].p_filesz % tmp[y].p_align != 0) ? 1 : 0)) * tmp[y].p_align);
	*/
	len += sizeof(woody->key);
	lseg->hdata->p_memsz += len; 
	lseg->hdata->p_filesz += len; 
}

int			add_to_end_segment(t_woody *woody, t_segments *lseg, char *content, size_t content_len)
{
	int		i_jmp;
	char	*code;
	size_t	jmpaddr;
	char	*tmp;

	if ((i_jmp = jmpchr(content, content_len)) < 0)
		return (1);
	jmpaddr = woody->elf_hdr->e_entry - ((lseg->hdata->p_vaddr + lseg->code_len) + (i_jmp + 5));
	ft_memcpy(content + i_jmp + 1, &jmpaddr, sizeof(jmpaddr));
	//jmpaddr = reverse_bytes(jmpaddr);

	code = malloc(woody->len);
	ft_memcpy(code, woody->bindest, woody->len);
	ft_memcpy(code + lseg->hdata->p_offset + lseg->code_len, content, content_len);
	ft_memcpy(code + lseg->hdata->p_offset + lseg->code_len + content_len, &(woody->key), sizeof(woody->key));

	tmp = woody->bindest;
	woody->bindest = code;
	woody->elf_hdr = (Elf64_Ehdr *)woody->bindest;
	woody->elf_hdr->e_entry = lseg->hdata->p_vaddr + lseg->code_len;	//entry point
	ft_printf("entry : '%x'\n", woody->elf_hdr->e_entry);
	free(tmp);
	return (0);
}
