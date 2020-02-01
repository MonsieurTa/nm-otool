/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:36:14 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 11:42:41 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int	ptr_valid_range(void *start, uint32_t length, void *ptr)
{
	void*	end;

	end = start + length;
	if (ptr < start || ptr >= end)
		return (0);
	return (1);
}
