/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:04:18 by wta               #+#    #+#             */
/*   Updated: 2020/02/09 14:54:18 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm.h"

static int	process_symtab(t_nm *nm, void *lc)
{
	t_symtab_command	*sym;

	sym = (t_symtab_command*)lc;
	if (nm->mach_o.is_cigam)
		range_swap32((void*)sym + offsetof(t_symtab_command, symoff),
			(sizeof(t_symtab_command) - (sizeof(uint32_t) * 2)) / 4);
	if (handle_symtab(nm, sym) == -1)
		return (0);
	return (1);
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
			return (throw_error(nm, ERR_TRUNCATED_OR_MALFORMED));
		if (mach_o->is_cigam)
			range_swap32((void*)lc, sizeof(t_load_command) / 4);
		if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
			handle_sections(nm, (void*)lc);
		else if (lc->cmd == LC_SYMTAB && !process_symtab(nm, (void*)lc))
			return (-1);
		lc = (void*)lc + lc->cmdsize;
	}
	return (1);
}
