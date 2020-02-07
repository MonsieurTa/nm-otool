/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:06:26 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 19:12:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

void	push_result(t_nm *nm, uint64_t addr, uint8_t c, char *str)
{
	static char		bad_string_index[] = "bad string index";
	t_nm_result		node_content;
	t_list			*node;
	t_mach_o		*mach_o;

	mach_o = &nm->mach_o;
	ft_bzero(&node_content, sizeof(t_nm_result));
	format_symaddr(mach_o, c, node_content.symaddr, addr);
	node_content.symchar = c;
	node_content.symname = str ? str : bad_string_index;
	node = ft_lstnew(&node_content, sizeof(t_nm_result));
	ft_pushback(&mach_o->result, node);
}

t_list	*pop(t_list_info *list)
{
	t_list	*res;

	if (!list->size || !list->head)
		return (NULL);
	res = list->head;
	list->head = list->head->next;
	res->next = NULL;
	list->size--;
	return (res);
}

void	rm_list(t_list_info *list)
{
	t_list		*node;
	t_list		*tmp;
	uint32_t	i;

	i = -1;
	node = list->head;
	while (node && ++i < list->size)
	{
		tmp = node;
		node = node->next;
		ft_memdel((void**)&tmp->content);
		ft_memdel((void**)&tmp);
	}
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
}
