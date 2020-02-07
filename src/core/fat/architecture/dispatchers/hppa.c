/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hppa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 18:55:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*g_hppa[] = {
	"hppa", "hppa_7100lc",
};

char	*hppa(cpu_subtype_t subtype)
{
	uint32_t	len;

	len = sizeof(g_hppa) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return g_hppa[subtype];
	return NULL;
}
