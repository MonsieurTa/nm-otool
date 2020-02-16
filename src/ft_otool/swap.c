/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:59:13 by wta               #+#    #+#             */
/*   Updated: 2020/02/16 14:59:24 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		swap_section_64(void *ptr)
{
	ptr = ptr + 32;
	*(uint64_t*)ptr = byte_swap64(*(uint64_t*)ptr);
	*(uint64_t*)ptr = byte_swap64(*(uint64_t*)ptr + 1);
	range_swap32(ptr, (sizeof(t_section_64) - 48) / 4);
}

void		swap_section(void *ptr)
{
	ptr = ptr + 32;
	range_swap32(ptr, (sizeof(t_section) - 32) / 4);
}
