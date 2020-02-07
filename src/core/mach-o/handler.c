/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:28:59 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 16:03:31 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	parse_mach_o(t_nm *nm)
{
	t_mach_o	*mach_o;

	mach_o = &nm->mach_o;
	mach_o->magic = *(uint32_t*)(mach_o->content);
	if (!get_mach_o_spec(nm))
		return (0);
	if (!handle_load_commands(nm))
		return (0);
	return (1);
}

int			handle_mach_o(t_nm *nm)
{
	parse_mach_o(nm);
	sort(&nm->mach_o.result, cmp_addr);
	print_result(nm->mach_o.result.head);
	rm_list(&nm->mach_o.sections);
	rm_list(&nm->mach_o.result);
	return (1);
}
