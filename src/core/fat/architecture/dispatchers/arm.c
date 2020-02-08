/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 18:05:03 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>


char	*arm(cpu_subtype_t subtype)
{
	static char	*arm_names[] = {
		"arm",        NULL,       NULL,      NULL,
		NULL,         "arm v4t,", "arm v6",  "arm v5tej",
		"arm xscale", "arm v7",   "arm v7f", "arm v7s",
		"arm v7k",    "arm v6m",  "arm v7m", "arm v7em",
		"arm v8"
	};
	uint32_t	len;

	len = sizeof(arm_names) / sizeof(char*);
	if ((uint32_t)(uint32_t)subtype < len)
		return arm_names[subtype];
	return NULL;
}