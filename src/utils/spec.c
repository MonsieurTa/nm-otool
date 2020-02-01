/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:07:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 11:08:24 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>

int		is_32(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM);
}

int		is_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

int		is_swap(uint32_t magic)
{
	return (magic == MH_CIGAM || magic == MH_CIGAM_64);
}
