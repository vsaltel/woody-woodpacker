#include "woody.h"

int	free_ret(t_woody *woody, int ret)
{
	free(woody->filename);
	if (woody->elf_hdr)
		munmap(woody->elf_hdr, woody->stat.st_size);
	if (woody->fd > 0)
		close(woody->fd);
	return (ret);
}

void	init_woody(t_woody *woody)
{
	woody->filename = NULL;
	woody->elf_hdr = NULL;
	woody->fd = 0;
}

int	ft_woody(t_woody *woody)
{
	display_elf_info(woody->elf_hdr);
	get_section(woody->elf_hdr, woody->binary);
	return (0);
}
