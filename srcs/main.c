#include "woody.h"

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
		else
			woody->filename = ft_strdup(argv[i]);
	}
	if (!woody->filename)
		woody->filename = ft_strdup("a.out");
}

int	main(int argc, char **argv)
{
	int		ret;
	t_woody	woody;

	init_woody(&woody);
	parse_param(&woody, argc, argv);
	woody.fd = open_file(woody.filename);	
	if (woody.fd < 0)
		return (free_ret(&woody, 1));
	ret = stat_file(&woody);
	if (ret)
		return (free_ret(&woody, ret));
	woody.binary = mmap(NULL, woody.stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, woody.fd, 0);
	woody.elf_hdr = (Elf64_Ehdr *)woody.binary;
	if (woody.elf_hdr == MAP_FAILED)
	{
		ft_dprintf(2, "woody_woodpacker: mmap fail\n");
		return (free_ret(&woody, 3));
	}
	ret = 4;
	if (!check_elf(woody.elf_hdr, woody.filename))	
		ret = ft_woody(&woody);
	return (free_ret(&woody, ret));
}
