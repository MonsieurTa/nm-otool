/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:49:57 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 11:19:33 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
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

int		main(int argc, char *argv[])
{
	t_stat	filestat;
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
			fstat(fd, &filestat);
			nm.content = mmap(NULL, filestat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
			close(fd);
			if (filestat.st_size >= 4)
				nm_start(&nm);
			munmap(nm.content, filestat.st_size);

			// TODO: move this
			t_list *node = nm.result.head;
			while (node) {
				t_nm_result *res = (t_nm_result*)node->content;
				if (res->symchar != '-')
					ft_printf("%s %c %s\n", res->symaddr, res->symchar, res->symname);
				node = node->next;
			}
		}
	}
	return (0);
}
