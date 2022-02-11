#ifndef WOODY_H
# define WOODY_H

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <elf.h>
#include <stdio.h>

# include "libft.h"

extern void		inject_func(void);
extern size_t	inject_size;
extern size_t	code_size;

typedef struct s_woody
{
	char		*filename;
	char		*binary;
	char		*bindest;
	int			v;
	int			c;
	int			s;
	int			fd;
	int			fd_dest;
	struct stat	stat;
	Elf64_Ehdr	*elf_hdr;
	size_t		len;
	uint64_t	key;
}				t_woody;

typedef struct s_segments
{
	Elf64_Phdr	*begin;
	Elf64_Phdr	*hdata;
	int			hdata_index;
	size_t		free_space;
	uint64_t	code_off;
	uint64_t	code_len;
	uint64_t	code_deb;
	size_t		seg_len;
}				t_segments;

typedef struct s_section
{
	char		*data;
	size_t		len;
}				t_section;


int			stat_file(t_woody *woody);
int			open_file(char *arg);
int			write_file(int fd, char *content, size_t len);
int			create_file(char *name);

int			free_ret(t_woody *woody, int ret);
void		init_woody(t_woody *woody);
size_t		memlen(char *deb, char *dest);
int			ft_woody(t_woody *woody);
int			opcodechr(char *str, size_t len, char opcode);
Elf64_Addr	reverse_bytes(Elf64_Addr bytes);
void		display_injection(t_woody *woody, t_segments *seg);

int			check_elf(Elf64_Ehdr *elf_hdr, char *arg);
void		display_elf_info(Elf64_Ehdr *elf_hdr);

Elf64_Shdr	*get_section_by_name(Elf64_Ehdr *elf_hdr, char *binary, char *name);
t_section	*get_data_section(t_section *dest, Elf64_Shdr *sh, char *binary);
int			set_section(Elf64_Ehdr *elf_hdr, char *binary);
void		update_section_pos(t_woody *woody, t_segments *lseg, size_t offset);

void		display_segment_info(Elf64_Ehdr *elf_hdr, char *binary);
int			check_data_available(t_woody *woody, t_segments *seg);
int			get_index_hdata(Elf64_Ehdr *elf_hdr, char *binary);
int			init_segments(t_segments *seg, Elf64_Ehdr *elf_hdr, char *binary);
int			add_to_end_segment(t_woody *woody, t_segments *lseg);
void		edit_segment_size(t_woody *woody, t_segments *lseg);


void		encrypt(t_woody *woody, t_segments *seg);
uint64_t	keygen(void);

#endif
