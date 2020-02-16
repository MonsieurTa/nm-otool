/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:59:56 by wta               #+#    #+#             */
/*   Updated: 2020/02/16 15:02:12 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_nm.h"
#include "ft_otool.h"

void		format_addr(t_mach_o *mach_o, char dst[], uint64_t addr)
{
	static const char	base[] = "0123456789abcdef";
	uint32_t			i;

	ft_strcpy(dst, mach_o->is_64 ? "0000000000000000" : "00000000");
	i = mach_o->is_64 ? 16 : 8;
	while (i-- && addr)
	{
		dst[i] = base[addr % 16];
		addr /= 16;
	}
}

void		hexdump_byte(char dst[], uint8_t value)
{
	static const char	base[] = "0123456789abcdef";
	uint32_t			i;

	ft_memcpy(dst, "00 ", 3);
	i = 2;
	while (i-- && value)
	{
		dst[i] = base[value % 16];
		value /= 16;
	}
}

void		format_hexdump(char dst[], void *ptr, uint32_t len)
{
	uint32_t			i;

	i = 0;
	ft_memset(dst, (int)'\0', 49);
	while (len--)
	{
		hexdump_byte(dst + i, *(uint8_t*)ptr);
		ptr++;
		i += 3;
	}
}

void		print_text_hexdump(t_nm *nm, void *ptr, void *end, uint64_t addr)
{
	char		addr_str[17];
	char		hexdump[49];
	uint32_t	len;

	ft_printf("%s:\n", nm->curr_argv);
	ft_printf("Contents of (__TEXT,__text) section\n");
	while (ptr < end)
	{
		len = (uint32_t)(end - ptr);
		len = len < 16 ? len : 16;
		format_addr(&nm->mach_o, addr_str, addr);
		format_hexdump(hexdump, ptr, len);
		ft_printf("%s\t%s\n", addr_str, hexdump);
		ptr += 16;
		addr += 16;
	}
}
