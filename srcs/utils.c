#include "woody.h"

int	free_ret(t_woody *woody, int ret)
{
	free(woody->filename);
	if (woody->binary)
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
	woody->binary = NULL;
	woody->bindest = NULL;
	woody->v = 0;
	woody->c = 0;
	woody->s = 0;
	woody->fd = -1;
	woody->fd_dest = -1;
	woody->elf_hdr = NULL;
	woody->len = 0;
	woody->key = 0;
}

size_t	memlen(char *deb, char *dest)
{
	size_t i;

	i = 0;
	while (deb != dest)
	{
		i++;
		deb++;
	}
	return (i);
}

Elf64_Addr reverse_bytes(Elf64_Addr bytes)
{
	int	len;
    Elf64_Addr aux = 0;
    uint8_t byte;
    int i;

	len = sizeof(Elf64_Addr);
	i = 0;
    while(i < len)
    {
        byte = (bytes >> i) & 0xff;
        aux |= byte << (32 - 8 - i);
		i += 8;
    }
    return (aux);
}

int	opcodechr(char *str, size_t len, char opcode)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == opcode)
			return ((int)i);
		i++;
	}
	return (-1);
}

void	display_injection(t_woody *woody, t_segments *seg)
{
	char	*c;
	size_t	i;

	i = 0;
	c = woody->bindest + seg->code_off + seg->code_len;
	ft_printf("Injection code :\n");
	while (i < inject_size)
	{
		ft_printf("\\x%02hhx", c[i]);
		i++;
	}
	write(1, "\n", 1);
}
