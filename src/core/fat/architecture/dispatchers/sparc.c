/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 18:56:07 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*g_sparc[] = {
	"sparc",
};

char	*sparc(cpu_subtype_t subtype)
{
	if (!subtype)
		return g_sparc[subtype];
	return NULL;
}
