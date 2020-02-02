/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:04:49 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 16:28:07 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "nm.h"

void	handle_sections(t_nm *nm, void *segment_command)
{
	uint32_t	nsects;
	uint32_t	offset;

	offset = nm->is_64 ?
		offsetof(t_segment_command_64, nsects)
		: offsetof(t_segment_command, nsects);
	nsects = *(uint32_t*)(segment_command + offset);
	nsects = nm->is_swap ? byte_swap32(nsects) : nsects;
	nm->nsects += nsects;
	store_sections(nm, segment_command + nm->segment_size, nsects);
}

void	store_sections(t_nm *nm, void *ptr, uint32_t nsects)
{
	t_list		*node;
	uint32_t	offset;
	uint32_t	i;

	offset = nm->section_size;
	i = -1;
	while (++i < nsects)
	{
		node = ft_lstnew_mallocfree(ptr, (size_t)offset);
		ft_pushback(&nm->sections, node);
		ptr += offset;
	}
}

void	*find_section(t_list_info *sections, void *nlist)
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
