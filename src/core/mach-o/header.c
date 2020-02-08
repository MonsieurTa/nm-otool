/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:07:33 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 19:53:30 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	get_mach_o_header_size(t_nm *nm)
{
	if (is_32(nm->mach_o.magic))
		return ((nm->mach_o.header_size = sizeof(t_mach_header)) != 0);
	else if (is_64(nm->mach_o.magic))
		return ((nm->mach_o.header_size = sizeof(t_mach_header_64)) != 0);
	return (throw_error(nm, ERR_NOT_MACH_O));
}
