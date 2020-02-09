/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:34:43 by wta               #+#    #+#             */
/*   Updated: 2020/02/09 18:10:49 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_nm.h"

static uint32_t	has_null_byte(char *str, void *eof)
{
	uint32_t	i;

	i = 0;
	while ((void*)(str + i) < eof)
	{
		if (str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void		print_result(t_nm *nm)
{
	t_list		*node;
	t_nm_result *res;
	void		*eof;

	node = nm->mach_o.result.head;
	eof = nm->content + nm->filestat.st_size;
	while (node)
	{
		res = (t_nm_result*)node->content;
		if (!has_null_byte(res->symname, eof))
		{
			write(STDOUT_FILENO, res->symname,
			(size_t)(eof - (void*)res->symname));
			write(STDOUT_FILENO, "\n", 1);
		}
		else if (res->symchar != '-')
			ft_printf("%s %c %s\n", res->symaddr, res->symchar, res->symname);
		node = node->next;
	}
}

char		*sarchitecture(t_nm *nm)
{
	int	cputype;
	int cpusubtype;

	cputype = nm->fat.cputype & ~CPU_ARCH_MASK;
	cpusubtype = nm->fat.cpusubtype & ~CPU_SUBTYPE_MASK;
	if (cputype > 0 && cputype <= 18)
	{
		if (g_dispatchers[cputype])
			return (g_dispatchers[cputype](cpusubtype));
	}
	return (NULL);
}
