/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc88000.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/09 15:58:02 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*mc88000(cpu_subtype_t subtype)
{
	static char	*mc88000_names[] = {
		"MC88000",
		"MC88100",
		"MC88110",
	};
	uint32_t	len;

	len = sizeof(mc88000_names) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return (mc88000_names[subtype]);
	return (mc88000_names[0]);
}
