/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:07:33 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 18:38:29 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int	get_mach_o_header_size(t_mach_o *mach_o)
{
	if (is_32(mach_o->magic))
		return ((mach_o->header_size = sizeof(t_mach_header)) != 0);
	else if (is_64(mach_o->magic))
		return ((mach_o->header_size = sizeof(t_mach_header_64)) != 0);
	return (0);
}
