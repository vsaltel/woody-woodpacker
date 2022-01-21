#ifndef WOODY_H
# define WOODY_H

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <elf.h>

# include "libft.h"

typedef struct s_woody
{
	char		*filename;
	int			fd;
	struct stat	stat;
	char		*binary;
	int			fd_dest;
	Elf64_Ehdr	*elf_hdr;
}				t_woody;

typedef struct s_section
{
	char		*data;
	size_t		len;
}				t_section;

int			stat_file(t_woody *woody);
int			open_file(char *arg);
int			write_file(int fd, char *content);
int			create_file(char *name);

int			free_ret(t_woody *woody, int ret);
void		init_woody(t_woody *woody);
int			ft_woody(t_woody *woody);

int			check_elf(Elf64_Ehdr *elf_hdr, char *arg);
void		display_elf_info(Elf64_Ehdr *elf_hdr);

Elf64_Shdr	*get_section_by_name(Elf64_Ehdr *elf_hdr, char *binary, char *name);
t_section	*get_data_section(t_section *dest, Elf64_Shdr *sh, char *binary);
int			set_section(Elf64_Ehdr *elf_hdr, char *binary);

Elf64_Phdr	*get_segment_hdata(Elf64_Ehdr *elf_hdr, char *binary);
int			add_to_end_segment(Elf64_Phdr *phdr, char *binary, char *content);

#endif
