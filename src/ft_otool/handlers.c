/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:53:31 by wta               #+#    #+#             */
/*   Updated: 2020/02/16 15:02:22 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"
#include "ft_otool.h"

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
