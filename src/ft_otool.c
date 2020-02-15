/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 07:37:10 by wta               #+#    #+#             */
/*   Updated: 2020/02/15 18:02:27 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stddef.h>
#include "ft_printf.h"
#include "ft_nm.h"

int			g_bin = BIN_OTOOL;

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

void		format_addr(t_mach_o *mach_o, char dst[], uint64_t addr)
{
	static const char	base[] = "0123456789abcdef";
	uint32_t			i;

	ft_strcpy(dst, mach_o->is_64 ? "0000000000000000" : "00000000");
	i = mach_o->is_64 ? 16 : 8;
	while (i-- && addr)
	{
		dst[i] = base[addr % 16];
		addr /= 16;
	}
}

void		hexdump_byte(char dst[], uint8_t value)
{
	static const char	base[] = "0123456789abcdef";
	uint32_t			i;

	ft_memcpy(dst, "00 ", 3);
	i = 2;
	while (i-- && value)
	{
		dst[i] = base[value % 16];
		value /= 16;
	}
}

void		format_hexdump(char dst[], void *ptr, uint32_t len)
{
	uint32_t			i;

	i = 0;
	ft_memset(dst, (int)'\0', 49);
	while (len--)
	{
		hexdump_byte(dst + i, *(uint8_t*)ptr);
		ptr++;
		i += 3;
	}
}

void		print_text_hexdump(t_nm *nm, void *ptr, void *end, uint64_t addr)
{
	char		addr_str[17];
	char		hexdump[49];
	uint32_t	len;

	ft_printf("%s:\n", nm->curr_argv);
	ft_printf("Contents of (__TEXT,__text) section\n");
	while (ptr < end)
	{
		len = (uint32_t)(end - ptr);
		len = len < 16 ? len : 16;
		format_addr(&nm->mach_o, addr_str, addr);
		format_hexdump(hexdump, ptr, len);
		ft_printf("%s\t%s\n", addr_str, hexdump);
		ptr += 16;
		addr += 16;
	}
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
	ptr = nm->mach_o.content + offset;
	if (!ptr_valid_range(nm->mach_o.content, nm->filestat.st_size, ptr + size))
		return (throw_error(nm, ERR_TRUNCATED_OR_MALFORMED));
	print_text_hexdump(nm, ptr, ptr + size, addr);
	return (1);
}

int			seek_text_section(t_nm *nm, void *ptr, uint32_t nsects)
{
	uint32_t		i;

	i = -1;
	while (++i < nsects)
	{
		if (!ptr_valid_range(nm->mach_o.content, nm->filestat.st_size,
		ptr + nm->mach_o.section_size))
			return (throw_error(nm, ERR_TRUNCATED_OR_MALFORMED));
		nm->section = ptr;
		if (ft_strequ((char*)nm->section, SECT_TEXT)
		&& ft_strequ((char*)nm->section + 16, SEG_TEXT))
			return (nm->section != NULL);
		ptr += nm->mach_o.section_size;
	}
	return (0);
}

int			has_text_section(t_nm *nm, void *ptr)
{
	uint32_t		nsects_offset;
	uint32_t		nsects;

	nsects_offset = nm->mach_o.is_64 ? offsetof(t_segment_command_64, nsects)
		: offsetof(t_segment_command, nsects);
	nsects = *(uint32_t*)(ptr + nsects_offset);
	if (seek_text_section(nm, ptr + nm->mach_o.segment_size, nsects))
		return (1);
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
	return (0);
}

int			otool_handle_mach_o(t_nm *nm)
{
	nm->mach_o.magic = *(uint32_t*)nm->mach_o.content;
	if (!get_mach_o_spec(nm))
		return (0);
	return (seek_text_lc_command(nm));
}

int			otool_handle_fat(t_nm *nm)
{
	t_fat		*fat;

	fat = &nm->fat;
	ft_memcpy((void*)&fat->fat_header, nm->content, sizeof(t_fat_header));
	get_fat_spec(nm);
	if (nm->found_host_arch == 1)
		return (handle_fat_arch_struct(nm, otool_handle_mach_o));
	else if (!nm->found_host_arch)
		return (process_fat(nm, otool_handle_mach_o));
	return (nm->found_host_arch);
}

int 		main(int argc, char *argv[])
{
	t_nm		nm;
	int			fd;
	int			i;
	int			ret;

	if (argc == 1)
		return (0);
	i = 0;
	ret = 1;
	while (ret > 0 && ++i < argc)
	{
		ft_bzero(&nm, sizeof(t_nm));
		nm.curr_argv = argv[i];
		nm.bin_location= argv[0];
		if ((fd = open(argv[i], O_RDONLY)) != -1)
			ret = process(&nm, fd, otool_handle_mach_o, otool_handle_fat);
	}
	return (ret <= 0);
}
