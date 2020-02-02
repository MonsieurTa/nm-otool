/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:45:02 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 17:46:19 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "nm.h"

uint32_t	byte_swap32(uint32_t x)
{
	return (((x >> 24) & 0xff) | (((x >> 16) & 0xff) << 8)
	| ((x >> 8) & 0xff) << 16 | (x & 0xff) << 24);
}

uint64_t	byte_swap64(uint64_t x)
{
	return ((x & 0x00000000000000FFUL) << 56 | (x & 0x000000000000FF00UL) << 40
	| (x & 0x0000000000FF0000UL) << 24 | (x & 0x00000000FF000000UL) << 8
	| (x & 0x000000FF00000000UL) >> 8 | (x & 0x0000FF0000000000UL) >> 24
	| (x & 0x00FF000000000000UL) >> 40 | (x & 0xFF00000000000000UL) >> 56);
}

void		range_swap32(void *start, uint32_t len)
{
	uint32_t	*ptr;

	ptr = (uint32_t*)start;
	while (len--)
	{
		*ptr = byte_swap32(*ptr);
		ptr++;
	}
}

void	nlist_swap(t_mach_o *mach_o, void *nlist)
{
	uint32_t	n_value_offset;
	void		*ptr;

	*(uint32_t*)nlist = byte_swap32(*(uint32_t*)nlist);
	if (mach_o->is_64)
	{
		n_value_offset = offsetof(t_nlist_64, n_value);
		ptr = nlist + n_value_offset;
		*(uint64_t*)ptr = byte_swap64(*(uint64_t*)ptr);
	}
	else
	{
		n_value_offset = offsetof(t_nlist, n_value);
		ptr = nlist + n_value_offset;
		*(uint32_t*)ptr = byte_swap32(*(uint32_t*)ptr);
	}
}
