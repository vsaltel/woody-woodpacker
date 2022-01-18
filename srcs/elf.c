#include "woody.h"

int	check_elf(Elf64_Ehdr *elfs, char *elf, char *arg)
{
	if ((unsigned char)elf[0] == '\x7f' && ft_strncmp(elf + 1, "ELF", 3))
	{
		ft_dprintf(2, "woody_woodpacker : %s: Not a elf file\n", arg);
		return (1);
	}
	if ((unsigned char)elf[EI_CLASS] > 7)
	{
		ft_dprintf(2, "woody_woodpacker : %s: The file was not recognized as a valid object file\n", arg);
		return (1);
	}
	if ((unsigned char)elf[EI_CLASS] != ELFCLASS64 && (unsigned char)elf[EI_CLASS] != EI_OSABI)
	{
		ft_dprintf(2, "woody_woodpacker : %s: Not a 64 bits file\n", arg);
		return (1);
	}
	if ((unsigned char)elf[EI_CLASS] == EI_OSABI)
	{
		if ((unsigned char)elf[EI_OSABI] == ELFOSABI_LINUX)
    		ft_dprintf(2, "Linux binary\n");
		else if ((unsigned char)elf[EI_OSABI] == ELFOSABI_SYSV)
			ft_dprintf(2, "SYSV binary\n");
		else if ((unsigned char)elf[EI_OSABI] == ELFOSABI_HPUX)
			ft_dprintf(2, "HP-UX binary\n");
	}
	printf("EI_OSABI : %d\n", EI_NIDENT);
	printf("elfs : %d %hhx", elfs->e_type, (unsigned char)elf[EI_CLASS]);
	return (0);
}
