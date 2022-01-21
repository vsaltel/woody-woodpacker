#include "woody.h"

int	main(int argc, char **argv)
{
	int		ret;
	t_woody	woody;

	init_woody(&woody);
	if (argc == 1)
		woody.filename = ft_strdup("a.out");
	else
		woody.filename = ft_strdup(argv[1]);
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
		ft_dprintf(2, "woody_woodpacker : mmap fail\n");
		return (free_ret(&woody, 3));
	}
	ret = 4;
	if (!check_elf(woody.elf_hdr, woody.filename))	
		ret = ft_woody(&woody);
	return (free_ret(&woody, ret));
}
