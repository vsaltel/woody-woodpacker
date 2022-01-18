#ifndef WOODY_H
# define WOODY_H

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "elf.h"
#include "sys/syscall.h"

#include <stdio.h>

# include "libft.h"

typedef struct s_woody
{
	char		*filename;
	int			fd;
	struct stat	stat;
	char		*elf;
	Elf64_Ehdr	*elfs;
}				t_woody;

int		stat_file(t_woody *woody);
int		open_file(char *arg);
int		check_elf(Elf64_Ehdr *elfs, char *elf, char *arg);
int		free_ret(t_woody *woody, int ret);
void	init_woody(t_woody *woody);
int		ft_woody(t_woody *woody);

#endif
