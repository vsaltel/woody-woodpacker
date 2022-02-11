#include "woody.h"

void		edit_segment_size(t_segments *lseg)
{
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
