#include "woody.h"

void	display_system(Elf64_Ehdr *elf_hdr)
{
	if ((unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_SYSV
			|| (unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_NONE)
		ft_dprintf(2, "Unix System V binary (version %u)\n", (unsigned char)elf_hdr->e_ident[EI_ABIVERSION]);
	else if ((unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_LINUX)
		ft_dprintf(2, "Linux binary (version %u)\n", (unsigned char)elf_hdr->e_ident[EI_ABIVERSION]);
	else if ((unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_HPUX)
		ft_dprintf(2, "HP-UX binary (version %u)\n", (unsigned char)elf_hdr->e_ident[EI_ABIVERSION]);
	else if ((unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_NETBSD)
		ft_dprintf(2, "NetBSD binary (version %u)\n", (unsigned char)elf_hdr->e_ident[EI_ABIVERSION]);
	else if ((unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_SOLARIS)
		ft_dprintf(2, "Solaris binary (version %u)\n", (unsigned char)elf_hdr->e_ident[EI_ABIVERSION]);
	else if ((unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_IRIX)
		ft_dprintf(2, "IRIX binary (version %u)\n", (unsigned char)elf_hdr->e_ident[EI_ABIVERSION]);
	else if ((unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_FREEBSD)
		ft_dprintf(2, "FreeBSD binary (version %u)\n", (unsigned char)elf_hdr->e_ident[EI_ABIVERSION]);
	else if ((unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_TRU64)
		ft_dprintf(2, "TRU64 binary (version %u)\n", (unsigned char)elf_hdr->e_ident[EI_ABIVERSION]);
	else if ((unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_ARM)
		ft_dprintf(2, "ARM binary (version %u)\n", (unsigned char)elf_hdr->e_ident[EI_ABIVERSION]);
	else if ((unsigned char)elf_hdr->e_ident[EI_OSABI] == ELFOSABI_STANDALONE)
		ft_dprintf(2, "Standalone binary (version %u)\n", (unsigned char)elf_hdr->e_ident[EI_ABIVERSION]);
}

void	display_elf_info(Elf64_Ehdr *elf_hdr)
{
	ft_dprintf(2, "Elf version %u\n", (unsigned char)elf_hdr->e_ident[EI_VERSION]);
	display_system(elf_hdr);
	ft_dprintf(2, "e_ident size : %u\n", (unsigned char)elf_hdr->e_ident[EI_NIDENT]);
}

int	check_elf(Elf64_Ehdr *elf_hdr, char *arg)
{
	if (ft_strncmp((const char *)elf_hdr->e_ident + EI_MAG0, "\x7f""ELF", 4))
	{
		ft_dprintf(2, "woody_woodpacker : %s: Not a elf file\n", arg);
		return (1);
	}
	if ((unsigned char)elf_hdr->e_ident[EI_CLASS] > 7)
	{
		ft_dprintf(2, "woody_woodpacker : %s: The file was not recognized as a valid object file\n", arg);
		return (1);
	}
	if ((unsigned char)elf_hdr->e_ident[EI_CLASS] != ELFCLASS64)
	{
		ft_dprintf(2, "woody_woodpacker : %s: Not a 64 bits file\n", arg);
		return (1);
	}
	display_elf_info(elf_hdr);
	return (0);
}
