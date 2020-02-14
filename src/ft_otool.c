/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 07:37:10 by wta               #+#    #+#             */
/*   Updated: 2020/02/14 13:59:28 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stddef.h>
#include "ft_nm.h"
#include "ft_printf.h"

void		swap_section_64(void *ptr)
{
	ptr = ptr + 32;
	*(uint64_t*)ptr = byte_swap64(*(uint64_t*)ptr);
	*(uint64_t*)ptr = byte_swap64(*(uint64_t*)ptr + 1);
	range_swap32(ptr, (sizeof(t_section_64) - 48) / 4);
}

void		swap_section(void *ptr)
{
	ptr = ptr + 32;
	range_swap32(ptr, (sizeof(t_section) - 32) / 4);
}

int			handle_text_lc_command(t_nm *nm)
{
	void		*ptr;
	uint64_t	addr;
	uint64_t	size;
	uint64_t	offset;

	ptr = nm->section;
	if (!ptr)
		return (0);
	if (nm->mach_o.is_cigam)
		nm->mach_o.is_64 ? swap_section_64(ptr) : swap_section(ptr);
	addr = nm->mach_o.is_64 ? *(uint64_t*)(ptr + 32) : *(uint32_t*)(ptr + 32);
	size = nm->mach_o.is_64 ? *(uint64_t*)(ptr + 40) : *(uint32_t*)(ptr + 36);
	offset = nm->mach_o.is_64 ? *(uint32_t*)(ptr + 48) : *(uint32_t*)(ptr + 40);
	ft_printf("%x\n", addr);
	ft_printf("%x\n", size);
	ft_printf("%x\n", offset);
	return (1);
}

void		*seek_text_section(t_nm *nm, void *ptr, uint32_t nsects)
{
	uint32_t		i;

	i = -1;
	while (++i < nsects)
	{
		nm->section = ptr;
		if (ft_strequ((char*)nm->section, SECT_TEXT))
			return (nm->section);
		ptr += nm->mach_o.section_size;
	}
	return (NULL);
}

int			has_text_section(t_nm *nm, void *ptr)
{
	t_section_64	*section;
	uint32_t		name_offset;
	uint32_t		nsects_offset;
	uint32_t		nsects;

	name_offset = nm->mach_o.is_64 ? offsetof(t_segment_command_64, segname)
		: offsetof(t_segment_command, segname);
	nsects_offset = nm->mach_o.is_64 ? offsetof(t_segment_command_64, nsects)
		: offsetof(t_segment_command, nsects);
	section = NULL;
	if (ft_strequ((char*)ptr + name_offset, SEG_TEXT))
	{
		nsects = *(uint32_t*)(ptr + nsects_offset);
		if (seek_text_section(nm, ptr + nm->mach_o.segment_size, nsects))
			return (1);
	}
	return (0);
}

int			seek_text_lc_command(t_nm *nm)
{
	t_mach_o		*mach_o;
	t_load_command	*lc;
	uint32_t		i;

	mach_o = &nm->mach_o;
	lc = (void*)mach_o->content + mach_o->header_size;
	i = -1;
	while (++i < mach_o->ncmds)
	{
		if (!ptr_valid_range(mach_o->content, nm->filestat.st_size, (void*)lc))
			return (throw_error(nm, ERR_TRUNCATED_OR_MALFORMED));
		if (mach_o->is_cigam)
			range_swap32((void*)lc, sizeof(t_load_command) /  4);
		if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
		{
			if (has_text_section(nm, (void*)lc))
				return (handle_text_lc_command(nm));
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (1);
}

int			otool_handle_mach_o(t_nm *nm) {
	nm->mach_o.magic = *(uint32_t*)nm->mach_o.content;
	if (!get_mach_o_spec(nm))
		return (0);
	if (!seek_text_lc_command(nm))
		return (0);
	return (1);
}

int			otool_handle_fat(t_nm *nm) {
	(void)nm;
	return (0);
}

int 		main(int argc, char *argv[])
{
	t_nm		nm;
	int			i;
	int			fd;

	if (argc == 1)
		return (0);
	i = 0;
	while (++i < argc)
	{
		ft_bzero(&nm, sizeof(t_nm));
		nm.curr_argv = argv[i];
		nm.bin_location= argv[0];
		if ((fd = open(argv[i], O_RDONLY)) != -1)
			process(&nm, fd, otool_handle_mach_o, otool_handle_fat);
	}
	return (0);
}
