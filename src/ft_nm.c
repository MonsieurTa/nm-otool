/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:49:57 by wta               #+#    #+#             */
/*   Updated: 2020/02/09 17:04:17 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include <stddef.h>
#include "libft.h"
#include "ft_nm.h"

static void	process(t_nm *nm, int fd)
{
	if (fstat(fd, &nm->filestat) == -1)
		return ;
	if (!S_ISREG(nm->filestat.st_mode))
		return ;
	nm->content = mmap(NULL, nm->filestat.st_size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	close(fd);
	if (nm->filestat.st_size < 4)
		throw_error(nm, ERR_NOT_VALID);
	else if ((nm->is_fat = is_fat(*(uint32_t*)nm->content)))
		handle_fat(nm);
	else if ((nm->mach_o.content = nm->content))
		handle_mach_o(nm);
	munmap(nm->content, nm->filestat.st_size);
}

int			main(int argc, char *argv[])
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
		nm.bin_location = argv[0];
		if ((fd = open(argv[i], O_RDONLY)) != -1)
			process(&nm, fd);
	}
	return (0);
}
