/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:49:57 by wta               #+#    #+#             */
/*   Updated: 2020/02/07 19:12:43 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include <stddef.h>
#include "libft.h"
#include "ft_nm.h"

char	g_archive_prefix[] = "!<arch>\n";

int		main(int argc, char *argv[])
{
	t_nm		nm;
	int			fd;
	int			i;

	if (argc == 1)
		return (0);
	i = 0;
	while (++i < argc)
	{
		ft_bzero(&nm, sizeof(t_nm));
		nm.curr_argv = argv[i];
		if ((fd = open(argv[i], O_RDONLY)) != -1)
		{
			fstat(fd, &nm.filestat);
			nm.content = mmap(NULL, nm.filestat.st_size,
				PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
			close(fd);
			if (nm.filestat.st_size >= 4 && !handle_fat(&nm))
				handle_mach_o(&nm);
			munmap(nm.content, nm.filestat.st_size);
		}
	}
	return (0);
}
