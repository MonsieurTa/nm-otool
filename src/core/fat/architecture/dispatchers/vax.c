/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vax.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 18:55:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*g_vax[] = {
	"vax", "vax780",  "vax785",  "vax750",
	"vax730",  "uvaxi",   "uvaxii",  "vax8200",
	"vax8500", "vax8600", "vax8650", "vax8800",
	"uvaxiii",
};

char	*vax(cpu_subtype_t subtype)
{
	uint32_t	len;

	len = sizeof(g_vax) / sizeof(char*);
	if ((uint32_t)subtype < len)
		return g_vax[subtype];
	return NULL;
}
