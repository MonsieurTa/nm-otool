/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:20:31 by wta               #+#    #+#             */
/*   Updated: 2020/02/15 17:23:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include "ft_nm.h"
#include "ft_printf.h"

int		process(t_nm *nm, int fd,
	int (*mach_o_handler)(t_nm*), int (*fat_handler)(t_nm*))
{
	if (fstat(fd, &nm->filestat) == -1)
		return (-1);
	if (!S_ISREG(nm->filestat.st_mode))
		return (-1);
	nm->content = mmap(NULL, nm->filestat.st_size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	close(fd);
	if (nm->filestat.st_size < 4)
		return (throw_error(nm, ERR_NOT_VALID));
	else if ((nm->is_fat = is_fat(*(uint32_t*)nm->content)))
		return (fat_handler(nm));
	else if ((nm->mach_o.content = nm->content) != NULL)
		return (mach_o_handler(nm));
	munmap(nm->content, nm->filestat.st_size);
	return (0);
}
