/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:49:57 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 17:07:05 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include <stddef.h>
#include "ft_printf.h"
#include "libft.h"
#include "nm.h"

char	g_archive_prefix[] = "!<arch>\n";

int		nm_start(t_nm *nm)
{
	nm->magic = *(uint32_t*)(nm->content);
	if (!get_spec_from_magic(nm))
		return (0);
	if (!handle_load_commands(nm))
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

int		main(int argc, char *argv[])
{
	t_nm	nm;
	int		fd;
	int		i;

	if (argc == 1)
		return (0);
	i = 0;
	while (++i < argc)
	{
		ft_bzero(&nm, sizeof(nm));
		if ((fd = open(argv[i], O_RDONLY)) != -1)
		{
			fstat(fd, &nm.filestat);
			nm.content = mmap(NULL, nm.filestat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
			close(fd);
			if (nm.filestat.st_size >= 4)
				nm_start(&nm);
			ft_printf("%x\n", nm.magic);
			sort(&nm.result, cmp_addr);

			t_list *node = nm.result.head;
			while (node) {
				t_nm_result *res = (t_nm_result*)node->content;
				if (res->symchar != '-')
					ft_printf("%s %c %s\n", res->symaddr, res->symchar, res->symname);
				node = node->next;
			}

			munmap(nm.content, nm.filestat.st_size);
			// TODO: move this
		}
	}
	return (0);
}
