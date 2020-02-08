/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:16:16 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 19:26:21 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm.h"

static uint32_t	get_offsetof_offset(uint8_t is_64)
{
	return (is_64 ?
		offsetof(t_fat_arch_64, offset) : offsetof(t_fat_arch, offset));
}

static uint32_t get_offsetof_size(uint8_t is_64)
{
	return (is_64 ?
		offsetof(t_fat_arch_64, size) : offsetof(t_fat_arch, size));
}

static void		get_offsets(t_nm *nm, void *ptr)
{
	t_fat		*fat;
	uint32_t	offset;

	fat = &nm->fat;
	offset = get_offsetof_offset(fat->is_64);
	fat->offset_to_mach_o = fat->is_64 ?
		*(uint64_t*)(ptr + offset) : *(uint32_t*)(ptr + offset);
	offset = get_offsetof_size(fat->is_64);
	nm->fat.mach_o_size = fat->is_64 ?
		*(uint64_t*)(ptr + offset) : *(uint32_t*)(ptr + offset);
}

int				handle_fat_arch_struct(t_nm *nm)
{
	void		*ptr;
	t_fat		*fat;

	fat = &nm->fat;
	ptr = nm->fat.fat_arch_struct;
	if (fat->is_cigam)
		fat->is_64 ? swap_fat_arch_64(ptr) : swap_fat_arch(ptr);
	fat->cputype = *(cpu_type_t*)ptr;
	fat->cpusubtype = *((cpu_type_t*)ptr + 1);
	get_offsets(nm, ptr);
	nm->mach_o.content = nm->content + fat->offset_to_mach_o;
	if (ptr_valid_range(nm->content, nm->filestat.st_size,
		nm->mach_o.content + fat->mach_o_size))
		return handle_mach_o(nm);
	else
		return throw_error(nm, ERR_TRUNCATED_OR_MALFORMED);
}
