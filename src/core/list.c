/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:06:26 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 16:41:45 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm.h"

void	push_result(t_nm *nm, uint64_t addr, uint8_t c, char *str)
{
	t_nm_result	node_content;
	t_list		*node;

	ft_bzero(&node_content, sizeof(t_nm_result));
	format_symaddr(nm, c, node_content.symaddr, addr);
	node_content.symchar = c;
	node_content.symname = ft_strdup(str);
	node = ft_lstnew(&node_content, sizeof(t_nm_result));
	ft_pushback(&nm->result, node);
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
