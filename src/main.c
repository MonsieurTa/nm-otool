/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:49:57 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 17:48:08 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include <stddef.h>
#include "ft_printf.h"
#include "libft.h"
#include "nm.h"

char	g_archive_prefix[] = "!<arch>\n";

int		parse_mach_o(t_mach_o *mach_o)
{
	mach_o->magic = *(uint32_t*)(mach_o->content);
	if (!get_mach_o_spec(mach_o))
		return (0);
	if (!handle_load_commands(mach_o))
		return (0);
	return (1);
}

int		cmp_addr(t_nm_result *a, t_nm_result *b)
{
	int32_t	name_diff;

	if ((name_diff = ft_strcmp(a->symname, b->symname)) == 0)
		return (ft_strcmp(a->symaddr, b->symaddr));
	return (name_diff);
}

int		handle_mach_o(t_mach_o *mach_o)
{
	if (mach_o->filestat.st_size >= 4)
		parse_mach_o(mach_o);
	sort(&mach_o->result, cmp_addr);
	return (1);
}

void	print_result(t_list *head)
{
	t_list	*node;

	node = head;
	while (node) {
		t_nm_result *res = (t_nm_result*)node->content;
		if (res->symchar != '-')
			ft_printf("%s %c %s\n", res->symaddr, res->symchar, res->symname);
		node = node->next;
	}
}

int		main(int argc, char *argv[])
{
	t_mach_o	*mach_o;
	t_nm		nm;
	int			fd;
	int			i;

	if (argc == 1)
		return (0);
	i = 0;
	while (++i < argc)
	{
		ft_bzero(&nm, sizeof(nm));
		if ((fd = open(argv[i], O_RDONLY)) != -1)
		{
			mach_o = &nm.mach_o;
			fstat(fd, &mach_o->filestat);
			mach_o->content = mmap(NULL, mach_o->filestat.st_size,
				PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
			close(fd);
			handle_mach_o(mach_o);
			print_result(mach_o->result.head);
			munmap(mach_o->content, mach_o->filestat.st_size);
		}
	}
	return (0);
}
