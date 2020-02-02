/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:29:44 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 19:06:18 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		cmp_addr(t_nm_result *a, t_nm_result *b)
{
	int32_t	name_diff;

	if ((name_diff = ft_strcmp(a->symname, b->symname)) == 0)
		return (ft_strcmp(a->symaddr, b->symaddr));
	return (name_diff);
}
