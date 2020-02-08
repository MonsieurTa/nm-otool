/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:23:13 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 18:07:05 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include "ft_nm.h"

char	*(*g_dispatchers[])(cpu_subtype_t) = {
	NULL,  vax,     NULL,   NULL, NULL,    NULL,
	mc680, x86,     NULL,   NULL, mc98000, hppa,
	arm,   mc88000, sparc,  i860, NULL,    NULL,
	ppc,
};
