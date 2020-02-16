/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 15:05:49 by wta               #+#    #+#             */
/*   Updated: 2020/02/16 15:06:45 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm.h"

static uint32_t	get_offsetof_offset(uint8_t is_64)
{
	return (is_64 ?
		offsetof(t_fat_arch_64, offset) : offsetof(t_fat_arch, offset));
}

static uint32_t	get_offsetof_size(uint8_t is_64)
{
	return (is_64 ?
		offsetof(t_fat_arch_64, size) : offsetof(t_fat_arch, size));
}

void			get_offsets(t_nm *nm, void *ptr)
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
