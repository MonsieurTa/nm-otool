/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vax.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/09 15:55:44 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*vax(cpu_subtype_t subtype)
{
	static char	*vax_names[] = {
		"vax", "vax780", "vax785", "vax750",
		"vax730", "uvaxi", "uvaxii", "vax8200",
		"vax8500", "vax8600", "vax8650", "vax8800",
		"uvaxiii",
	};
	uint32_t	len;

	len = sizeof(vax_names) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return (vax_names[subtype]);
	return (vax_names[0]);
}
