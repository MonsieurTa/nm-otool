/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc680.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 18:55:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*g_mc680[] = 	{
	NULL, "mc680x0_all", "mc68030", "mc68040", "mc68030_only",
};

char	*mc680(cpu_subtype_t subtype)
{
	uint32_t	len;

	len = sizeof(g_mc680) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return g_mc680[subtype];
	return NULL;
}
