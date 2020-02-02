/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:30:53 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 19:33:14 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		handle_fat(t_nm *nm)
{
	t_fat	*fat;
	uint32_t		magic;

	if (is_fat(*(uint32_t*)nm->content))
	{
		fat = &nm->fat;
		ft_memcpy((void*)&fat->fat_header, nm->content, sizeof(t_fat_header));
		magic = fat->fat_header.magic;
		fat->is_64 = is_64(magic);
		fat->is_swap = is_cigam(magic);
		if (fat->is_swap)
			fat->fat_header.nfat_arch = byte_swap32(fat->fat_header.nfat_arch);
		fat->fat_arch_size = nm->fat.is_64 ?
			sizeof(t_fat_arch_64) : sizeof(t_fat_arch);
	}
	else
		nm->mach_o.content = nm->content;
	return (1);
}
