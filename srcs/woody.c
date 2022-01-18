#include "woody.h"

int	free_ret(t_woody *woody, int ret)
{
	free(woody->filename);
	if (woody->elf)
		munmap(woody->elf, woody->stat.st_size);
	if (woody->fd > 0)
		close(woody->fd);
	return (ret);
}

void	init_woody(t_woody *woody)
{
	woody->filename = NULL;
	woody->elf = NULL;
	woody->fd = 0;
}

int	ft_woody(t_woody *woody)
{
	ft_printf("ok\n");
	return (0);
}
