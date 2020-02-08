/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hppa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 18:04:49 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>


char	*hppa(cpu_subtype_t subtype)
{
	static char	*hppa_names[] = {
		"hppa", "hppa_7100lc",
	};
	uint32_t	len;

	len = sizeof(hppa_names) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return hppa_names[subtype];
	return NULL;
}
