/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:06:26 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 11:27:20 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm.h"

void	push_result(t_nm *nm, uint64_t addr, uint8_t c, char *str)
{
	t_nm_result	node_content;
	t_list		*node;

	ft_bzero(&node_content, sizeof(t_nm_result));
	format_symaddr(c, node_content.symaddr, addr);
	node_content.symchar = c;
	node_content.symname = ft_strdup(str);
	node = ft_lstnew(&node_content, sizeof(t_nm_result));
	ft_pushback(&nm->result, node);
}
