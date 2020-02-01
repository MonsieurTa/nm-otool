/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:05:31 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 11:20:46 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "nm.h"

void	handle_symtab(t_nm *nm, t_symtab_command *sym)
{
	void		*nlist;
	uint32_t	offset;
	uint32_t	i;

	offset = nm->nlist_size;
	nlist = nm->content + sym->symoff;
	nm->strtab = nm->content + sym->stroff;
	nm->strtabsize = sym->strsize;
	i = -1;
	while (++i < sym->nsyms)
	{
		handle_symbol(nm, nlist);
		nlist = (void*)nlist + offset;
	}
}

void	handle_symbol(t_nm *nm, void *nlist)
{
	uint64_t	n_value;
	uint8_t		n_value_size;
	uint8_t		offset;
	uint8_t		c;
	char		*symname;

	offset = nm->is_64 ?
		offsetof(t_nlist_64, n_value) : offsetof(t_nlist, n_value);
	n_value_size = nm->is_64 ? sizeof(uint64_t) : sizeof(uint32_t);
	ft_memcpy(&n_value, nlist + offset, n_value_size);
	c = get_symbol_letter(nm, nlist);
	symname = nm->strtab + *(uint32_t*)nlist;
	push_result(nm, n_value, c, symname);
}

uint8_t	get_symbol_letter(t_nm *nm, void *nlist)
{
	uint8_t	n_type;

	n_type = *(uint8_t*)(nlist + sizeof(uint32_t));
	if (n_type & N_STAB)
		return ('-');
	else if ((n_type & N_TYPE) == N_UNDF)
	{
		if (n_type & N_EXT)
			return ('U');
	}
	else if ((n_type & N_TYPE) == N_SECT)
		return (match_symbol_section(nm, nlist, n_type));
	else if ((n_type & N_TYPE) == N_ABS)
		return ('A');
	else if ((n_type & N_TYPE) == N_INDR)
		return ('I');
	return (0);
}

uint8_t	match_symbol_section(t_nm *nm, void *nlist, uint8_t n_type)
{
	char	*sectname;
	void	*section;
	char	c;

	section = find_section(&nm->sections, nlist);
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
