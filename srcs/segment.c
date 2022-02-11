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
		ft_printf("\tp_vaddr %#lx, p_offset %#lx\n", segment[i].p_vaddr, segment[i].p_offset);
		ft_printf("\tp_flags %c%c%c, p_type %d\n", (segment[i].p_flags & PF_R ? 'R' : ' '), (segment[i].p_flags & PF_W ? 'W' : ' '), (segment[i].p_flags & PF_X ? 'X' : ' '), segment[i].p_type);
	}
}

int			check_data_available(t_woody *woody, t_segments *seg)
{
	size_t	i;
	char	*data;

	data = woody->bindest + seg->hdata->p_offset + seg->hdata->p_filesz;
	i = 0;
	while (data[i] == 0)
		i++;
	if (i < inject_size)
	{
		ft_dprintf(2, "woody-woodpacker: Not enough space in .text\n");
		ft_dprintf(2, "%d < %d\n", i, inject_size);
		return (1);
	}
	seg->free_space = i;
	return (0);
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
}

int			init_segments(t_segments *seg, Elf64_Ehdr *elf_hdr, char *binary)
{
	seg->begin = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	seg->hdata_index = get_index_hdata(elf_hdr, binary);
	seg->hdata = seg->begin + seg->hdata_index;
	seg->code_len = seg->hdata->p_filesz;
	seg->code_off = seg->hdata->p_offset;
	seg->code_deb = seg->hdata->p_vaddr;
	seg->seg_len = elf_hdr->e_phnum;
	return (0);
}

void		edit_segment_size(t_woody *woody, t_segments *lseg)
{
	(void)woody;

	lseg->hdata->p_memsz += inject_size; 
	lseg->hdata->p_filesz += inject_size; 
}

int			add_to_end_segment(t_woody *woody, t_segments *lseg)
{
	int		i_jmp;
	char	*code;
	size_t	jmpaddr;
	char	*tmp;
	uint64_t	reladdr;

	code = malloc(woody->len);
	tmp = code;
	ft_memcpy(tmp, woody->bindest, woody->len);
	tmp += lseg->hdata->p_offset + lseg->code_len;
	ft_memcpy(tmp, inject_func, inject_size);

	if ((i_jmp = opcodechr(tmp, inject_size, '\xe9')) < 0)
	{
		ft_dprintf(2, "woody-woodpacker : jmp not find\n");
		return (1);
	}
	jmpaddr = woody->elf_hdr->e_entry - ((lseg->hdata->p_vaddr + lseg->code_len) + (i_jmp + 5));
	ft_memcpy(tmp + i_jmp + 1, &jmpaddr, sizeof(jmpaddr));

	tmp += code_size;
	ft_memcpy(tmp, &(woody->key), sizeof(woody->key));
	tmp += sizeof(woody->key);

	reladdr = lseg->code_len + code_size;
	ft_memcpy(tmp , &(reladdr), sizeof(reladdr));
	tmp += sizeof(reladdr);
	ft_memcpy(tmp, &(lseg->code_len), sizeof(lseg->code_len));

	tmp = woody->bindest;
	woody->bindest = code;
	woody->elf_hdr = (Elf64_Ehdr *)woody->bindest;
	woody->elf_hdr->e_entry = lseg->hdata->p_vaddr + lseg->code_len;	//entry point
	free(tmp);
	return (0);
}
