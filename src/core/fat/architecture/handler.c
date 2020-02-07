/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:16:16 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 19:40:13 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_printf.h"
#include "ft_nm.h"

char	*sarchitecture(t_nm *nm)
{
	int	cputype;
	int cpusubtype;

	cputype = nm->fat.cputype & ~CPU_ARCH_MASK;
	cpusubtype = nm->fat.cpusubtype & ~CPU_SUBTYPE_MASK;
	if (cputype > 0 && cputype <= 18)
	{
		if (g_dispatchers[cputype])
			return g_dispatchers[cputype](cpusubtype);
	}
	return NULL;
}

void	handle_fat_arch_struct(t_nm *nm)
{
	void		*ptr;
	t_fat		*fat;
	uint64_t	offset_to_mach_o;
	uint32_t	off;

	fat = &nm->fat;
	ptr = nm->fat.fat_arch_struct;
	if (fat->is_cigam)
		fat->is_64 ? swap_fat_arch_64(ptr) : swap_fat_arch(ptr);
	nm->fat.cputype = *(cpu_type_t*)ptr;
	nm->fat.cpusubtype = *(cpu_type_t*)ptr + 1;
	off = fat->is_64 ?
		offsetof(t_fat_arch_64, offset) : offsetof(t_fat_arch, offset);
	offset_to_mach_o = fat->is_64 ?
		*(uint64_t*)(ptr + off) : *(uint32_t*)(ptr + off);
	off = fat->is_64 ?
		offsetof(t_fat_arch_64, size) : offsetof(t_fat_arch, size);
	nm->fat.mach_o_size = fat->is_64 ?
		*(uint64_t*)(ptr + off) : *(uint32_t*)(ptr + off);
	nm->mach_o.content = nm->content + offset_to_mach_o;
	if (nm->fat.fat_header.nfat_arch > 1)
		ft_printf("\n%s (for architecture %s): \n", nm->curr_argv, sarchitecture(nm));
	if (ptr_valid_range(nm->content, nm->filestat.st_size, nm->mach_o.content))
		handle_mach_o(nm);
}
