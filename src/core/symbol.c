/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:05:31 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 17:06:36 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "nm.h"

int		handle_symtab(t_nm *nm, t_symtab_command *sym)
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
		if (!ptr_valid_range(nm->content, nm->filestat.st_size, nlist)
		|| !handle_symbol(nm, nlist))
			return (0);
		nlist = (void*)nlist + offset;
	}
	return (1);
}

int		handle_symbol(t_nm *nm, void *nlist)
{
	uint64_t	n_value;
	uint8_t		n_value_size;
	uint8_t		offset;
	uint8_t		c;
	char		*symname;

	if (nm->is_swap)
		nlist_swap(nm, nlist);
	symname = nm->strtab + *(uint32_t*)nlist;
	if (!ptr_valid_range(nm->content, nm->filestat.st_size, symname))
		symname = NULL;
	offset = nm->is_64 ?
		offsetof(t_nlist_64, n_value) : offsetof(t_nlist, n_value);
	n_value_size = nm->is_64 ? sizeof(uint64_t) : sizeof(uint32_t);
	ft_memcpy(&n_value, nlist + offset, n_value_size);
	c = get_symbol_letter(nm, nlist);
	push_result(nm, n_value, c, symname);
	return (1);
}

uint8_t	get_symbol_letter(t_nm *nm, void *nlist)
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
		return (match_symbol_section(nm, nlist, n_type));
	else if ((n_type & N_TYPE) == N_ABS)
		return ('A' - tolower);
	else if ((n_type & N_TYPE) == N_INDR)
		return ('I' - tolower);
	return ('?');
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
