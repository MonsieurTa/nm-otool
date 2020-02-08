/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc98000.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 18:03:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>


char	*mc98000(cpu_subtype_t subtype)
{
	static char	*mc98000_names[] = {
		"mc98000_all", "mc98601",
	};
	uint32_t	len;

	len = sizeof(mc98000_names) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return mc98000_names[subtype];
	return NULL;
}
