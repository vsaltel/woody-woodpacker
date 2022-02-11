#include "woody.h"

int		usage(char *prog)
{
	ft_dprintf(2, "Usage: %s [OPTIONS]... [FILE]\n\t-v \t\tVerbose mode\n\t-s \
		Display sections informations\n\t-c \
		Display injected opcode\n\t-k hexnum \tSet encryption key\n", prog);
	return (1);
}

void	parse_param(t_woody *woody, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-v")) 	
			woody->v = 1;
		else if (!ft_strcmp(argv[i], "-c")) 	
			woody->c = 1;
		else if (!ft_strcmp(argv[i], "-s")) 	
			woody->s = 1;
		else if (!ft_strcmp(argv[i], "-k")) 	
		{
			if (argv[++i])
				woody->key = read_hex(argv[i]);
		}
		else if (!woody->filename)
			woody->filename = ft_strdup(argv[i]);
	}
}

int	main(int argc, char **argv)
{
	int		ret;
	t_woody	woody;

	init_woody(&woody);
	parse_param(&woody, argc, argv);
	if (!woody.filename)
		return (usage(argv[0]));
	woody.fd = open_file(woody.filename);	
	if (woody.fd < 0)
		return (free_ret(&woody, 2));
	if ((ret = stat_file(&woody)))
		return (free_ret(&woody, ret));
	woody.binary = mmap(NULL, woody.stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, woody.fd, 0);
	woody.elf_hdr = (Elf64_Ehdr *)woody.binary;
	if (woody.elf_hdr == MAP_FAILED)
	{
		ft_dprintf(2, "woody_woodpacker: mmap fail\n");
		return (free_ret(&woody, 4));
	}
	if ((ret = check_file(&woody)))
		return (free_ret(&woody, ret));
	ret = ft_woody(&woody);
	return (free_ret(&woody, ret));
}
