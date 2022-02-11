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

int			get_index_hdata(t_woody *woody, Elf64_Ehdr *elf_hdr, char *binary)
{
	Elf64_Phdr	*segment;
	int			i;

	i = -1;
	segment = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	if ((char *)segment < binary || (char *)segment > (binary + woody->len))
	{
		ft_dprintf(2, "woody-woodpacker: Broken elf file\n");
		return (-1);
	}
	while (++i < elf_hdr->e_phnum)
		if ((segment[i].p_flags & PF_R) && (segment[i].p_flags & PF_X))
				return (i);
	return (-2);
}

int			init_segments(t_woody *woody, t_segments *seg, Elf64_Ehdr *elf_hdr, char *binary)
{
	seg->begin = (Elf64_Phdr *)(binary + elf_hdr->e_phoff);
	if ((seg->hdata_index = get_index_hdata(woody, elf_hdr, binary)) < 0)
		return (1);
	seg->hdata = seg->begin + seg->hdata_index;
	seg->code_len = seg->hdata->p_filesz;
	seg->code_off = seg->hdata->p_offset;
	seg->code_deb = seg->hdata->p_vaddr;
	seg->seg_len = elf_hdr->e_phnum;
	return (0);
}
