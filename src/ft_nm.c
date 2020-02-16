/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:49:57 by wta               #+#    #+#             */
/*   Updated: 2020/02/16 16:14:32 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include "libft.h"
#include "ft_nm.h"

int			g_bin = BIN_NM;

int			exec_nm(t_nm *nm, char *filename, char *bin_location)
{
	int	fd;

	ft_bzero(nm, sizeof(t_nm));
	nm->curr_argv = filename;
	nm->bin_location = bin_location;
	if ((fd = open(filename, O_RDONLY)) != -1)
		return (process(nm, fd, nm_handle_mach_o, nm_handle_fat));
	else
		throw_error(nm, ERR_NO_SUCH_FILE_OR_DIR);
	return (0);
}

int			main(int argc, char *argv[])
{
	t_nm		nm;
	int			ret;
	int			i;

	if (argc == 1)
		return (exec_nm(&nm, "a.out", argv[0]) <= 0);
	i = 0;
	ret = 1;
	while (ret > 0 && ++i < argc)
		ret = exec_nm(&nm, argv[i], argv[0]);
	return (ret <= 0);
}
