/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:30:53 by wta               #+#    #+#             */
/*   Updated: 2020/02/15 16:19:46 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm.h"
#include "ft_printf.h"

int			nm_handle_fat(t_nm *nm)
{
	t_fat		*fat;

	fat = &nm->fat;
	ft_memcpy((void*)&fat->fat_header, nm->content, sizeof(t_fat_header));
	get_fat_spec(nm);
	if (nm->found_host_arch == 1)
		return (handle_fat_arch_struct(nm, nm_handle_mach_o));
	else if (!nm->found_host_arch)
		return (process_fat(nm, nm_handle_mach_o));
	return (nm->found_host_arch);
}
