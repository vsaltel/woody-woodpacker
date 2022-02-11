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
	uint32_t	*c;
	size_t		i;

	i = 0;
	c = (uint32_t *)(woody->bindest + seg->code_off + seg->code_len);
	ft_printf("Injection code :\n");
	while (i < inject_size / 4)
	{
		ft_printf("0x%08x\t", c[i]);
		i++;
		if (i != 0 && i % 4 == 0)
			write(1, "\n", 1);
	}
	ft_printf("\n");
}

uint64_t	read_hex(char *in)
{
	uint64_t	ret;
	int			i;

	if (!in)
		return (0);
	i = 0;
	ret = 0;
	while (i < 16 && in[i])
	{
		if (in[i] >= '0' && in[i] <= '9')
		{
			ret = ret << 4;
			ret += in[i] - '0';
		}
		else if (in[i] >= 'a' && in[i] <= 'f')
		{
			ret = ret << 4;
			ret += (in[i] - 'a' + 10);
		}
		else
			return (0);
		i++;
	}
	return (ret);
}
