#ifndef WOODY_H
# define WOODY_H

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <elf.h>
#include <time.h>
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


/*	file.c */
int			stat_file(t_woody *woody);
int			open_file(char *arg);
int			write_file(int fd, char *content, size_t len);
int			create_file(char *name);

/*	utils.c */
int			free_ret(t_woody *woody, int ret);
void		init_woody(t_woody *woody);
size_t		memlen(char *deb, char *dest);
int			ft_woody(t_woody *woody);
int			opcodechr(char *str, size_t len, char opcode);
void		display_injection(t_woody *woody, t_segments *seg);
uint64_t	read_hex(char *in);

/*	elf.c */
int			check_elf(Elf64_Ehdr *elf_hdr, char *arg);
void		display_elf_info(Elf64_Ehdr *elf_hdr);

/*	segment_utils.c */
void		display_segment_info(Elf64_Ehdr *elf_hdr, char *binary);
int			check_data_available(t_woody *woody, t_segments *seg);
int			get_index_hdata(t_woody *woody, Elf64_Ehdr *elf_hdr, char *binary);
int			init_segments(t_woody *woody, t_segments *seg, Elf64_Ehdr *elf_hdr, char *binary);

/*	segment.c */
int			add_to_end_segment(t_woody *woody, t_segments *lseg);
void		edit_segment_size(t_segments *lseg);

/*	encrypt.c */
void		encrypt(t_woody *woody, t_segments *seg);
uint64_t	keygen(void);

/*	check_file.c */
int			check_file(t_woody *woody);

#endif
