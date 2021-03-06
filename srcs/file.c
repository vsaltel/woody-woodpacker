#include "woody.h"

int	stat_file(t_woody *woody)
{
	if (syscall(SYS_fstat, woody->fd, &woody->stat) != 0)
	{
		ft_dprintf(2, "woody_woodpacker : fstat fail\n");
		return (2);
	}
	if (S_ISDIR(woody->stat.st_mode))
	{
		ft_dprintf(2, "woody_woodpacker : %s: is Directory\n", woody->filename);
		return (3);
	}
	woody->len = woody->stat.st_size;
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

int write_file(int fd, char *content, size_t len)
{
	if (fd > -1 && content)
		return (write(fd, content, len));
	return (-1);
}

int	create_file(char *name)
{
	if (name)
		return (open(name, O_TRUNC | O_WRONLY | O_CREAT, 0751));
	return (-1);
}
