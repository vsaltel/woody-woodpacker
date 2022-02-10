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
	woody->elf_hdr = NULL;
	woody->fd = -1;
	woody->fd_dest = -1;
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

void	display_injection(void)
{
	char	*c;
	size_t	i;

	i = 0;
	c = (char *)inject_func;
	while (i < inject_size)
	{
		printf("\\x%02hhx", c[i]);
		i++;
	}
}
