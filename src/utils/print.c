/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:34:43 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 19:03:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_nm.h"

void	print_result(t_list *head)
{
	t_list		*node;
	t_nm_result *res;

	node = head;
	while (node)
	{
		res = (t_nm_result*)node->content;
		if (res->symchar != '-')
			ft_printf("%s %c %s\n", res->symaddr, res->symchar, res->symname);
		node = node->next;
	}
}

char	*sarchitecture(t_nm *nm)
{
	int	cputype;
	int cpusubtype;

	cputype = nm->fat.cputype & ~CPU_ARCH_MASK;
	cpusubtype = nm->fat.cpusubtype & ~CPU_SUBTYPE_MASK;
	if (cputype > 0 && cputype <= 18)
	{
		if (g_dispatchers[cputype])
			return g_dispatchers[cputype](cpusubtype);
	}
	return (NULL);
}
