/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:06:51 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 18:50:43 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

void	format_symaddr(t_mach_o *mach_o, char c, char dst[], uint64_t addr)
{
	static const char	base[] = "0123456789abcdef";
	uint32_t			i;

	ft_strcpy(dst, mach_o->is_64 ? "                " : "        ");
	if (c == 'U')
		return ;
	ft_strcpy(dst, mach_o->is_64 ? "0000000000000000" : "00000000");
	i = mach_o->is_64 ? 16 : 8;
	while (i-- && addr)
	{
		dst[i] = base[addr % 16];
		addr /= 16;
	}
}
