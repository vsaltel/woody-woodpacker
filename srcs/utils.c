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

int	jmpchr(char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == '\xe9')
			return ((int)i);
		i++;
	}
	return (-1);
}
