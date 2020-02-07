/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x86.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 19:22:26 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>
#include "ft_printf.h"
char	*g_x86[] = 	{
	"x86_64",            "x86_archi1", "x86_64_h",    "i386",
	"386",               "486",        "486sx",       "pent",
	"pentpro",           "pentii_m3",  "pentii_m5",   "celeron",
	"celeron_mobile",    "pentium_3",  "pentium_3_m", "pentium_3_xeon",
	"pentium_m",         "pentium_4",  "pentium_4_m", "pentium_itanium",
	"pentium_itanium_2", "xeon",       "xeon_mp",     "intel_family_max",
};

char	*x86(cpu_subtype_t subtype)
{
	uint32_t	len;

	len = sizeof(g_x86) / sizeof(char*);
	if (subtype == CPU_SUBTYPE_X86_ALL)
		return (g_x86[0]);
	if (subtype == CPU_SUBTYPE_X86_ARCH1)
		return (g_x86[1]);
	if (subtype == CPU_SUBTYPE_X86_64_H)
		return (g_x86[2]);
	if (subtype == CPU_SUBTYPE_I386_ALL)
		return (g_x86[3]);
	if (subtype == CPU_SUBTYPE_486)
		return (g_x86[4]);
	if (subtype == CPU_SUBTYPE_486SX)
		return (g_x86[5]);
	if (subtype == CPU_SUBTYPE_PENT)
		return (g_x86[6]);
	if (subtype == CPU_SUBTYPE_PENTPRO)
		return (g_x86[7]);
	if (subtype == CPU_SUBTYPE_PENTII_M3)
		return (g_x86[8]);
	if (subtype == CPU_SUBTYPE_PENTII_M5)
		return (g_x86[9]);
	if (subtype == CPU_SUBTYPE_CELERON)
		return (g_x86[10]);
	if (subtype == CPU_SUBTYPE_CELERON_MOBILE)
		return (g_x86[11]);
	if (subtype == CPU_SUBTYPE_PENTIUM_3)
		return (g_x86[12]);
	if (subtype == CPU_SUBTYPE_PENTIUM_3_M)
		return (g_x86[13]);
	if (subtype == CPU_SUBTYPE_PENTIUM_3_XEON)
		return (g_x86[14]);
	if (subtype == CPU_SUBTYPE_PENTIUM_M)
		return (g_x86[15]);
	if (subtype == CPU_SUBTYPE_PENTIUM_4)
		return (g_x86[16]);
	if (subtype == CPU_SUBTYPE_PENTIUM_4_M)
		return (g_x86[17]);
	if (subtype == CPU_SUBTYPE_ITANIUM)
		return (g_x86[18]);
	if (subtype == CPU_SUBTYPE_ITANIUM_2)
		return (g_x86[19]);
	if (subtype == CPU_SUBTYPE_XEON)
		return (g_x86[20]);
	if (subtype == CPU_SUBTYPE_XEON_MP)
		return (g_x86[21]);
	if (subtype == CPU_SUBTYPE_INTEL_FAMILY_MAX)
		return (g_x86[22]);
	if (subtype == CPU_SUBTYPE_INTEL_MODEL_ALL)
		return (g_x86[23]);
	return NULL;
}
