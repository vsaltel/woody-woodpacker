#include "woody.h"

static int	remove_protection(Elf64_Phdr *hdata)
{
	if (!hdata)
		return (2);
	hdata->p_type = PT_LOAD;
	hdata->p_flags |= PF_W;
	hdata->p_flags |= PF_X;
	hdata->p_flags |= PF_R;
	return (0);
}

static void	print_info(t_woody *woody, t_segments *lseg)
{
	ft_printf("Encryption Key : \t\t%#lx\n", woody->key);
	ft_printf("Segment HDATA mem addr : \t%#lx\n", lseg->code_deb);
	ft_printf("Segment HDATA file offset : \t%#lx\n", lseg->code_off);
	ft_printf("Origin code lenght : \t\t%ld\n", lseg->code_len);
	ft_printf("Injection code size : \t\t%ld\n", inject_size);
	ft_printf("Free space lenght : \t\t%d\n", lseg->free_space);
	ft_printf("New entry point : \t\t%#lx\n", woody->elf_hdr->e_entry);
}

static int	set_binary_exe(t_woody *woody, t_segments *lseg)
{
	remove_protection(lseg->hdata);
	if (!woody->key)
		woody->key = keygen();
	edit_segment_size(lseg);
	add_to_end_segment(woody, lseg);
	encrypt(woody, lseg);
	return (0);
}

static int	set_binary(t_woody *woody)
{
	t_segments	lseg;

	if (init_segments(woody, &lseg, woody->elf_hdr, woody->bindest))
		return (1);
	if (check_data_available(woody, &lseg))
		return (2);
	if (woody->s)
	{
		ft_printf("Info segments before modifications :\n");
		display_segment_info(woody->elf_hdr, woody->bindest);
		write(1, "\n", 1);
	}
	set_binary_exe(woody, &lseg);
	if (woody->s)
	{
		ft_printf("Info segments after modifications :\n");
		display_segment_info(woody->elf_hdr, woody->bindest);
	}
	if (woody->v)
		print_info(woody, &lseg);
	if (woody->c)
		display_injection(woody, &lseg);
	return (0);
}

int			ft_woody(t_woody *woody)
{
	woody->bindest = malloc(woody->len);
	woody->bindest = ft_memcpy(woody->bindest, woody->binary, woody->len);
	woody->elf_hdr = (Elf64_Ehdr *)woody->bindest;
	if (woody->v)
		display_elf_info(woody->elf_hdr);
	set_binary(woody);
	if ((woody->fd_dest = create_file("woody")) > -1)
		write_file(woody->fd_dest, woody->bindest, woody->len);
	free(woody->bindest);
	return (0);
}
