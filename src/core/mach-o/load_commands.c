/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:04:18 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 18:54:54 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "nm.h"

static void	process_symtab(t_nm *nm, void *lc)
{
	t_mach_o			*mach_o;
	t_symtab_command	*sym;

	mach_o = &nm->mach_o;
	sym = (t_symtab_command*)lc;
	if (mach_o->is_swap)
		range_swap32((void*)sym + offsetof(t_symtab_command, symoff),
			(sizeof(t_symtab_command) - (sizeof(uint32_t) * 2)) / 4);
	handle_symtab(nm, sym);
}

int			handle_load_commands(t_nm *nm)
{
	t_mach_o				*mach_o;
	t_load_command			*lc;
	uint32_t				i;

	mach_o = &nm->mach_o;
	lc = (void*)mach_o->content + mach_o->header_size;
	i = -1;
	while (++i < mach_o->ncmds)
	{
		if (!ptr_valid_range(mach_o->content, nm->filestat.st_size, (void*)lc))
			return (0);
		if (mach_o->is_swap)
			range_swap32((void*)lc, sizeof(t_load_command) / 4);
		if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
			handle_sections(mach_o, (void*)lc);
		else if (lc->cmd == LC_SYMTAB)
			process_symtab(nm, (void*)lc);
		lc = (void*)lc + lc->cmdsize;
	}
	return (1);
}
