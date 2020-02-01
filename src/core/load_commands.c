/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:04:18 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 11:48:49 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "nm.h"

int		handle_load_commands(t_nm *nm)
{
	t_load_command			*lc;
	t_symtab_command		*sym;
	uint32_t				i;

	lc = (void*)nm->content + nm->header_size;
	i = -1;
	while (++i < nm->ncmds)
	{
		if (!ptr_valid_range(nm->content, nm->filestat.st_size, (void*)lc))
			return (0);
		if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
			handle_sections(nm, (void*)lc);
		else if (lc->cmd == LC_SYMTAB)
		{
			sym = (t_symtab_command*)(void*)lc;
			handle_symtab(nm, sym);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (1);
}
