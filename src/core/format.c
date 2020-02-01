/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:06:51 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 16:45:31 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

void	format_symaddr(t_nm *nm, char c, char dst[], uint64_t addr)
{
	static const char	base[] = "0123456789abcdef";
	uint32_t			i;

	if (c == 'U')
		return ((void)ft_strcpy(dst, nm->is_64 ?
			"                " : "        "));
	ft_strcpy(dst, nm->is_64 ?
		"0000000000000000" : "00000000");
	i = nm->is_64 ? 16 : 8;
	while (--i && addr)
	{
		dst[i] = base[addr % 16];
		addr /= 16;
	}
}
