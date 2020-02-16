/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seeker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:58:15 by wta               #+#    #+#             */
/*   Updated: 2020/02/16 15:07:41 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm.h"
#include "ft_otool.h"

int			seek_text_section(t_nm *nm, void *ptr, uint32_t nsects)
{
	uint32_t		i;

	i = -1;
	while (++i < nsects)
	{
		if (!ptr_valid_range(nm->mach_o.content, nm->filestat.st_size,
		ptr + nm->mach_o.section_size))
			return (throw_error(nm, ERR_TRUNCATED_OR_MALFORMED));
		nm->section = ptr;
		if (ft_strequ((char*)nm->section, SECT_TEXT)
		&& ft_strequ((char*)nm->section + 16, SEG_TEXT))
			return (nm->section != NULL);
		ptr += nm->mach_o.section_size;
	}
	return (0);
}

int			has_text_section(t_nm *nm, void *ptr)
{
	uint32_t		nsects_offset;
	uint32_t		nsects;

	nsects_offset = nm->mach_o.is_64 ? offsetof(t_segment_command_64, nsects)
		: offsetof(t_segment_command, nsects);
	nsects = *(uint32_t*)(ptr + nsects_offset);
	if (seek_text_section(nm, ptr + nm->mach_o.segment_size, nsects))
		return (1);
	return (0);
}

int			seek_text_lc_command(t_nm *nm)
{
	t_mach_o		*mach_o;
	t_load_command	*lc;
	uint32_t		i;

	mach_o = &nm->mach_o;
	lc = (void*)mach_o->content + mach_o->header_size;
	i = -1;
	while (++i < mach_o->ncmds)
	{
		if (!ptr_valid_range(mach_o->content, nm->filestat.st_size, (void*)lc))
			return (throw_error(nm, ERR_TRUNCATED_OR_MALFORMED));
		if (mach_o->is_cigam)
			range_swap32((void*)lc, sizeof(t_load_command) / 4);
		if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
		{
			if (has_text_section(nm, (void*)lc))
				return (handle_text_lc_command(nm));
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (0);
}
