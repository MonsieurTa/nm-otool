/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc88000.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 18:55:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*g_mc88000[] = {
	"MC88000",
	"MC88100",
	"MC88110",
};

char	*mc88000(cpu_subtype_t subtype)
{
	uint32_t	len;

	len = sizeof(g_mc88000) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return g_mc88000[subtype];
	return NULL;
}
