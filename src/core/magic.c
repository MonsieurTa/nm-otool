/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:10:14 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 16:19:26 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>
int		get_spec_from_magic(t_nm *nm)
{
	t_mach_header_64	mach_header;

	ft_bzero(&mach_header, sizeof(t_mach_header_64));
	if (!get_header_size(nm))
		return (0);
	ft_memcpy((void *)&mach_header, nm->content, nm->header_size);
	nm->ncmds = mach_header.ncmds;
	nm->is_64 = is_64(nm->magic);
	nm->is_swap = is_swap(nm->magic);
	nm->nlist_size = nm->is_64 ? sizeof(t_nlist_64) : sizeof(t_nlist);
	nm->section_size = nm->is_64 ? sizeof(t_section_64) : sizeof(t_section);
	nm->segment_size = nm->is_64 ?
		sizeof(t_segment_command_64) : sizeof(t_segment_command);
	if (nm->is_swap)
		nm->ncmds = byte_swap32(nm->ncmds);
	return (1);
}
