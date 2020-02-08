/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:30:53 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 20:09:12 by wta              ###   ########.fr       */
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
		if (!handle_fat_arch_struct(nm))
			return (0);
		ptr = ptr + nm->fat.fat_arch_size;
	}
	return (1);
}

static int	find_host_arch(t_nm *nm)
{
	void		*ptr;
	cpu_type_t	cputype;
	cpu_type_t	cpusubtype;
	uint32_t	i;

	ptr = nm->content + sizeof(t_fat_header);
	i = -1;
	while (++i < nm->fat.fat_header.nfat_arch)
	{
		nm->fat.fat_arch_struct = ptr;
		cputype = *(cpu_type_t*)ptr;
		cpusubtype = *((cpu_subtype_t*)ptr + 1);
		if (nm->fat.is_cigam)
		{
			cputype = byte_swap32(cputype);
			cpusubtype = byte_swap32(cpusubtype);
		}
		if (cputype == CPU_TYPE_X86_64
		&& (cpusubtype & ~CPU_SUBTYPE_MASK) == CPU_SUBTYPE_X86_ALL)
			return ((nm->found_host_arch = 1));
		ptr = ptr + nm->fat.fat_arch_size;
	}
	return (0);
}

int			handle_fat(t_nm *nm)
{
	t_fat		*fat;
	uint32_t	magic;

	if ((nm->is_universal = is_fat(*(uint32_t*)nm->content)))
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
		if (find_host_arch(nm))
			return (handle_fat_arch_struct(nm));
		process_fat(nm);
		return (1);
	}
	nm->mach_o.content = nm->content;
	return (-1);
}
