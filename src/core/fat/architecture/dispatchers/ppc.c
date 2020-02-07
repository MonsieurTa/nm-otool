/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 18:55:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*g_ppc[] = {
	"ppc",
	"ppc_601",
	"ppc_602",
	"ppc_603",
	"ppc_603e",
	"ppc_603ev",
	"ppc_604",
	"ppc_604e",
	"ppc_620",
	"ppc_750",
	"ppc_7400",
	"ppc_7450",
	"ppc_970",
};

char	*ppc(cpu_subtype_t subtype)
{
	uint32_t	len;

	if (subtype == CPU_SUBTYPE_POWERPC_970)
		return g_ppc[12];
	len = sizeof(g_ppc) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return g_ppc[subtype];
	return NULL;
}
