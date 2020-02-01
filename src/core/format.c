/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:06:51 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 11:26:11 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	format_symaddr(char c, char dst[], uint64_t addr)
{
	static const char	base[] = "0123456789abcdef";
	uint32_t			i;

	if (c == 'U')
		return ((void)ft_strcpy(dst, "                "));
	ft_strcpy(dst, "0000000000000000");
	i = 16;
	while (--i && addr)
	{
		dst[i] = base[addr % 16];
		addr /= 16;
	}
}
