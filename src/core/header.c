/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:07:33 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 11:07:38 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		get_header_size(t_nm *nm)
{
	if (is_32(nm->magic))
		return ((nm->header_size = sizeof(t_mach_header)) != 0);
	else if (is_64(nm->magic))
		return ((nm->header_size = sizeof(t_mach_header_64)) != 0);
	return (0);
}
