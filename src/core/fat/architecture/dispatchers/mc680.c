/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc680.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/09 15:58:55 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*mc680(cpu_subtype_t subtype)
{
	static char	*mc680_names[] = {
		NULL, "mc680x0", "mc68030", "mc68040", "mc68030_only",
	};
	uint32_t	len;

	len = sizeof(mc680_names) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return (mc680_names[subtype]);
	return (mc680_names[1]);
}
