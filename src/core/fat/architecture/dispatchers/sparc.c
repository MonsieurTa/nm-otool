/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/09 15:59:31 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*sparc(cpu_subtype_t subtype)
{
	static char	*sparc_names[] = {
		"sparc",
	};

	(void)subtype;
	return (sparc_names[0]);
}
