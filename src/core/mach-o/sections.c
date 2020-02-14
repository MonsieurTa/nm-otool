/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:04:49 by wta               #+#    #+#             */
/*   Updated: 2020/02/14 11:06:25 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "ft_nm.h"

static void	store_sections(t_mach_o *mach_o, void *ptr, uint32_t nsects)
{
	t_list		*node;
	uint32_t	offset;
	uint32_t	i;

	offset = mach_o->section_size;
	i = -1;
	while (++i < nsects)
	{
		node = ft_lstnew(ptr, (size_t)offset);
		ft_pushback(&mach_o->sections, node);
		ptr += offset;
	}
}

void		handle_sections(t_nm *nm, void *segment_command)
{
	t_mach_o	*mach_o;
	uint32_t	nsects;
	uint32_t	offset;

	mach_o = &nm->mach_o;
	offset = mach_o->is_64 ?
		offsetof(t_segment_command_64, nsects)
		: offsetof(t_segment_command, nsects);
	nsects = *(uint32_t*)(segment_command + offset);
	nsects = mach_o->is_cigam ? byte_swap32(nsects) : nsects;
	mach_o->nsects += nsects;
	store_sections(mach_o, segment_command + mach_o->segment_size, nsects);
}

void		*find_section(t_list_info *sections, void *nlist)
{
	t_list		*node;
	uint8_t		index;
	uint32_t	i;

	index = *(uint8_t*)(nlist + offsetof(t_nlist_64, n_sect)) - 1;
	if (index >= sections->size)
		return (NULL);
	node = sections->head;
	i = -1;
	while (++i < index)
		node = node->next;
	return (node->content);
}
