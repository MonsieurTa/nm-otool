/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_fat_arch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:58:27 by wta               #+#    #+#             */
/*   Updated: 2020/02/15 15:54:55 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ft_printf.h"

void	swap_fat_arch(void *ptr)
{
	range_swap32(ptr, sizeof(t_fat_arch) / 4);
}

void	swap_fat_arch_64(void *ptr)
{
	t_fat_arch_64	*fat_arch_64;

	fat_arch_64 = ptr;
	fat_arch_64->cputype = byte_swap32(fat_arch_64->cputype);
	fat_arch_64->cpusubtype = byte_swap32(fat_arch_64->cpusubtype);
	fat_arch_64->offset = byte_swap64(fat_arch_64->offset);
	fat_arch_64->size = byte_swap64(fat_arch_64->size);
	fat_arch_64->align = byte_swap32(fat_arch_64->align);
	fat_arch_64->reserved = byte_swap32(fat_arch_64->reserved);
}
