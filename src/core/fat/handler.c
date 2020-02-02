/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:30:53 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 18:30:59 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		handle_fat(t_nm *nm)
{
	t_fat_header	fat_header;
	uint32_t		magic;

	(void)fat_header;
	magic = *(uint32_t*)nm->content;
	if (is_fat(magic))
	{

	}
	else
		nm->mach_o.content = nm->content;
	return (1);
}
