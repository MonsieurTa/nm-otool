/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:28:59 by wta               #+#    #+#             */
/*   Updated: 2020/02/14 09:29:32 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_nm.h"

static int	parse_mach_o(t_nm *nm)
{
	t_mach_o	*mach_o;

	mach_o = &nm->mach_o;
	mach_o->magic = *(uint32_t*)(mach_o->content);
	if (!get_mach_o_spec(nm))
		return (0);
	if (handle_load_commands(nm) == -1)
		return (0);
	return (1);
}

int			nm_handle_mach_o(t_nm *nm)
{
	uint32_t	ret;

	ret = parse_mach_o(nm);
	if (ret)
	{
		sort(&nm->mach_o.result, cmp_addr);
		if (nm->fat.fat_header.nfat_arch > 1 && !nm->found_host_arch)
			ft_printf("\n%s (for architecture %s):\n",
			nm->curr_argv, sarchitecture(nm));
		print_result(nm);
	}
	rm_list(&nm->mach_o.sections);
	rm_list(&nm->mach_o.result);
	return (ret);
}
