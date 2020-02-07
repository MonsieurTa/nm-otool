/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:30:53 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 19:12:34 by wta              ###   ########.fr       */
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
		handle_fat_arch_struct(nm);
		ptr = ptr + nm->fat.fat_arch_size;
	}
	return (1);
}

int			handle_fat(t_nm *nm)
{
	t_fat		*fat;
	uint32_t	magic;

	if (is_fat(*(uint32_t*)nm->content))
	{
		fat = &nm->fat;
		ft_memcpy((void*)&fat->fat_header, nm->content, sizeof(t_fat_header));
		magic = fat->fat_header.magic;
		fat->is_64 = is_64(magic);
		fat->is_cigam = is_cigam(magic);
		if (fat->is_cigam)
			fat->fat_header.nfat_arch = byte_swap32(fat->fat_header.nfat_arch);
		fat->fat_arch_size = fat->is_64 ?
			sizeof(t_fat_arch_64) : sizeof(t_fat_arch);
		process_fat(nm);
		return (1);
	}
	nm->mach_o.content = nm->content;
	return (0);
}
