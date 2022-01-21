#include "woody.h"

int	free_ret(t_woody *woody, int ret)
{
	free(woody->filename);
	if (woody->elf_hdr)
		munmap(woody->binary, woody->stat.st_size);
	if (woody->fd > 0)
		close(woody->fd);
	if (woody->fd_dest)
		close(woody->fd);
	return (ret);
}

void	init_woody(t_woody *woody)
{
	woody->filename = NULL;
	woody->elf_hdr = NULL;
	woody->fd = -1;
	woody->fd_dest = -1;
}
