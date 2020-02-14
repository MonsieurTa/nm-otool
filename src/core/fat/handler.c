/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:30:53 by wta               #+#    #+#             */
/*   Updated: 2020/02/14 09:17:09 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm.h"

static int	process_fat(t_nm *nm)
{
	void		*ptr;
	uint32_t	i;

	ptr = nm->content + sizeof(t_fat_header);
	i = -1;
	while (++i < nm->fat.fat_header.nfat_arch)
	{
		nm->fat.fat_arch_struct = ptr;
		if (nm_handle_fat_arch_struct(nm) == -1)
			return (0);
		ptr = ptr + nm->fat.fat_arch_size;
	}
	return (1);
}

void		apply_host_arch(t_nm *nm, void *ptr)
{
	if (nm->fat.cputype == CPU_TYPE_X86_64
	&& (nm->fat.cpusubtype & ~CPU_SUBTYPE_MASK) == CPU_SUBTYPE_X86_ALL)
		nm->fat.fat_arch_struct = ptr;
}

static int	find_host_arch(t_nm *nm)
{
	void		*ptr;
	uint32_t	i;

	ptr = nm->content + sizeof(t_fat_header);
	i = -1;
	while (++i < nm->fat.fat_header.nfat_arch)
	{
		if (!ptr_valid_range(nm->content, nm->filestat.st_size,
		ptr + nm->fat.fat_arch_size))
			return (throw_error(nm, ERR_TRUNCATED_OR_MALFORMED));
		if (nm->fat.is_cigam)
			nm->fat.is_64 ? swap_fat_arch_64(ptr) : swap_fat_arch(ptr);
		nm->fat.cputype = *(cpu_type_t*)ptr;
		nm->fat.cpusubtype = *((cpu_type_t*)ptr + 1);
		get_offsets(nm, ptr);
		nm->mach_o.content = nm->content + nm->fat.offset_to_mach_o;
		if (!ptr_valid_range(nm->content, nm->filestat.st_size,
			nm->mach_o.content + nm->fat.mach_o_size))
			return (throw_error(nm, ERR_TRUNCATED_OR_MALFORMED));
		apply_host_arch(nm, ptr);
		ptr = ptr + nm->fat.fat_arch_size;
	}
	return (nm->fat.fat_arch_struct != NULL);
}

void		get_fat_spec(t_nm *nm)
{
	uint32_t	magic;

	magic = nm->fat.fat_header.magic;
	nm->fat.is_64 = is_64(magic);
	nm->fat.is_cigam = is_cigam(magic);
	if (nm->fat.is_cigam)
		nm->fat.fat_header.nfat_arch = byte_swap32(
			nm->fat.fat_header.nfat_arch);
	nm->fat.fat_arch_size = nm->fat.is_64 ?
		sizeof(t_fat_arch_64) : sizeof(t_fat_arch);
	nm->found_host_arch = find_host_arch(nm);
}

int			nm_handle_fat(t_nm *nm)
{
	t_fat		*fat;

	fat = &nm->fat;
	ft_memcpy((void*)&fat->fat_header, nm->content, sizeof(t_fat_header));
	get_fat_spec(nm);
	if (nm->found_host_arch == 1)
		return (nm_handle_fat_arch_struct(nm));
	else if (!nm->found_host_arch)
		return (process_fat(nm));
	return (nm->found_host_arch);
}
