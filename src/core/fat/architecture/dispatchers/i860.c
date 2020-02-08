/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i860.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 19:04:05 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>


char	*i860(cpu_subtype_t subtype)
{
	static char	*i860_names[] = {
		"i860", "i860 860",
	};
	uint32_t	len;

	len = sizeof(i860_names) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return i860_names[subtype];
	return (i860_names[0]);
}
