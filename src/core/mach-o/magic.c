/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:10:14 by wta               #+#    #+#             */
/*   Updated: 2020/02/09 14:54:28 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	get_mach_o_spec(t_nm *nm)
{
	t_mach_o			*mach_o;
	t_mach_header_64	mach_header;

	mach_o = &nm->mach_o;
	ft_bzero(&mach_header, sizeof(t_mach_header_64));
	if (get_mach_o_header_size(nm) == -1)
		return (0);
	ft_memcpy((void *)&mach_header, mach_o->content, mach_o->header_size);
	mach_o->ncmds = mach_header.ncmds;
	mach_o->is_64 = is_64(mach_o->magic);
	mach_o->is_cigam = is_cigam(mach_o->magic);
	mach_o->nlist_size = mach_o->is_64 ? sizeof(t_nlist_64) : sizeof(t_nlist);
	mach_o->section_size = mach_o->is_64 ?
		sizeof(t_section_64) : sizeof(t_section);
	mach_o->segment_size = mach_o->is_64 ?
		sizeof(t_segment_command_64) : sizeof(t_segment_command);
	if (mach_o->is_cigam)
		mach_o->ncmds = byte_swap32(mach_o->ncmds);
	return (1);
}
