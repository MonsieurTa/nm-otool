/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:05:31 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 18:05:23 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "nm.h"

int		handle_symtab(t_nm *nm, t_symtab_command *sym)
{
	t_mach_o	*mach_o;
	void		*nlist;
	uint32_t	offset;
	uint32_t	i;

	mach_o = &nm->mach_o;
	offset = mach_o->nlist_size;
	nlist = mach_o->content + sym->symoff;
	mach_o->strtab = mach_o->content + sym->stroff;
	mach_o->strtabsize = sym->strsize;
	i = -1;
	while (++i < sym->nsyms)
	{
		if (!ptr_valid_range(mach_o->content, nm->filestat.st_size, nlist)
		|| !handle_symbol(nm, nlist))
			return (0);
		nlist = (void*)nlist + offset;
	}
	return (1);
}

int		handle_symbol(t_nm *nm, void *nlist)
{
	t_mach_o	*mach_o;
	uint64_t	n_value;
	uint8_t		offset;
	uint8_t		c;
	char		*symname;

	mach_o = &nm->mach_o;
	if (mach_o->is_swap)
		nlist_swap(mach_o, nlist);
	symname = mach_o->strtab + *(uint32_t*)nlist;
	if (!ptr_valid_range(mach_o->content, nm->filestat.st_size, symname))
		symname = NULL;
	offset = mach_o->is_64 ?
		offsetof(t_nlist_64, n_value) : offsetof(t_nlist, n_value);
	ft_memcpy(&n_value, nlist + offset, mach_o->is_64 ?
		sizeof(uint64_t) : sizeof(uint32_t));
	c = get_symbol_letter(mach_o, nlist);
	push_result(mach_o, n_value, c, symname);
	return (1);
}

uint8_t	get_symbol_letter(t_mach_o *mach_o, void *nlist)
{
	uint8_t	n_type;
	uint8_t	tolower;

	n_type = *(uint8_t*)(nlist + sizeof(uint32_t));
	tolower = !(n_type & N_EXT) ? 'A' - 'a' : 0;
	if (n_type & N_STAB)
		return ('-');
	else if ((n_type & N_TYPE) == N_UNDF)
	{
		if (n_type & N_EXT)
			return ('U');
	}
	else if ((n_type & N_TYPE) == N_SECT)
		return (match_symbol_section(mach_o, nlist, n_type));
	else if ((n_type & N_TYPE) == N_ABS)
		return ('A' - tolower);
	else if ((n_type & N_TYPE) == N_INDR)
		return ('I' - tolower);
	return ('?');
}

uint8_t	match_symbol_section(t_mach_o *mach_o, void *nlist, uint8_t n_type)
{
	char	*sectname;
	void	*section;
	char	c;

	section = find_section(&mach_o->sections, nlist);
	if (!section)
		return (0);
	sectname = (char*)(section + offsetof(t_section_64, sectname));
	if (ft_strequ(sectname, SECT_TEXT))
		c = 'T';
	else if (ft_strequ(sectname, SECT_DATA))
		c = 'D';
	else if (ft_strequ(sectname, SECT_BSS))
		c = 'B';
	else
		c = 'S';
	if (!(n_type & N_EXT))
		c -= 'A' - 'a';
	return (c);
}
