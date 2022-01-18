#include "woody.h"

int	stat_file(t_woody *woody)
{
	if (fstat(woody->fd, &woody->stat) != 0)
	{
		ft_dprintf(2, "woody_woodpacker : fstat fail\n");
		return (2);
	}
	if (S_ISDIR(woody->stat.st_mode))
	{
		ft_dprintf(2, "woody_woodpacker : %s: is Directory\n", woody->filename);
		return (2);
	}
	return (0);
}

int	open_file(char *arg)
{
	int	fd;

	fd = open(arg, O_RDONLY);	
	if (fd < 0)
		ft_dprintf(2, "woody_woodpacker : %s: No such file or directory\n", arg);
	return (fd);
}
