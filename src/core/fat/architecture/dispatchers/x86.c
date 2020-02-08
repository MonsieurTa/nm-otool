/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x86.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:09:55 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 19:29:28 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/machine.h>
#include <unistd.h>

char	*x86(cpu_subtype_t subtype)
{
	static char	*x86_names[] = {
		"x86_64",            "x86_archi1", "x86_64h",    "i386",
		"486",               "486sx",      "pent",
		"pentpro",           "pentii_m3",  "pentii_m5",   "celeron",
		"celeron_mobile",    "pentium_3",  "pentium_3_m", "pentium_3_xeon",
		"pentium_m",         "pentium_4",  "pentium_4_m", "itanium",
		"itanium_2",         "xeon",       "xeon_mp",     "intel_family_max",
	};
	uint32_t	len;

	len = sizeof(x86_names) / sizeof(char*);
	if (subtype == CPU_SUBTYPE_I386_ALL)
		return (x86_names[3]);
	if (subtype == CPU_SUBTYPE_486)
		return (x86_names[4]);
	if (subtype == CPU_SUBTYPE_486SX)
		return (x86_names[5]);
	if (subtype == CPU_SUBTYPE_PENT)
		return (x86_names[6]);
	if (subtype == CPU_SUBTYPE_PENTPRO)
		return (x86_names[7]);
	if (subtype == CPU_SUBTYPE_PENTII_M3)
		return (x86_names[8]);
	if (subtype == CPU_SUBTYPE_PENTII_M5)
		return (x86_names[9]);
	if (subtype == CPU_SUBTYPE_CELERON)
		return (x86_names[10]);
	if (subtype == CPU_SUBTYPE_CELERON_MOBILE)
		return (x86_names[11]);
	if (subtype == CPU_SUBTYPE_PENTIUM_3)
		return (x86_names[12]);
	if (subtype == CPU_SUBTYPE_PENTIUM_3_M)
		return (x86_names[13]);
	if (subtype == CPU_SUBTYPE_PENTIUM_3_XEON)
		return (x86_names[14]);
	if (subtype == CPU_SUBTYPE_PENTIUM_M)
		return (x86_names[15]);
	if (subtype == CPU_SUBTYPE_PENTIUM_4)
		return (x86_names[16]);
	if (subtype == CPU_SUBTYPE_PENTIUM_4_M)
		return (x86_names[17]);
	if (subtype == CPU_SUBTYPE_ITANIUM)
		return (x86_names[18]);
	if (subtype == CPU_SUBTYPE_ITANIUM_2)
		return (x86_names[19]);
	if (subtype == CPU_SUBTYPE_XEON)
		return (x86_names[20]);
	if (subtype == CPU_SUBTYPE_XEON_MP)
		return (x86_names[21]);
	if (subtype == CPU_SUBTYPE_INTEL_FAMILY_MAX)
		return (x86_names[22]);
	if (subtype == CPU_SUBTYPE_X86_ALL)
		return (x86_names[0]);
	if (subtype == CPU_SUBTYPE_X86_ARCH1)
		return (x86_names[1]);
	if (subtype == CPU_SUBTYPE_X86_64_H)
		return (x86_names[2]);
	return (NULL);
}
