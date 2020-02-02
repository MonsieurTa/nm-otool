/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:34:43 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 18:36:06 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "nm.h"

void	print_result(t_list *head)
{
	t_list	*node;

	node = head;
	while (node) {
		t_nm_result *res = (t_nm_result*)node->content;
		if (res->symchar != '-')
			ft_printf("%s %c %s\n", res->symaddr, res->symchar, res->symname);
		node = node->next;
	}
}
