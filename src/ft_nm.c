/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:49:57 by wta               #+#    #+#             */
/*   Updated: 2020/02/15 16:33:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include "libft.h"
#include "ft_nm.h"

int			g_bin = BIN_NM;

int			main(int argc, char *argv[])
{
	t_nm		nm;
	int			fd;
	int			i;
	int			ret;

	if (argc == 1)
		return (0);
	i = 0;
	ret = 1;
	while (ret > 0 && ++i < argc)
	{
		ft_bzero(&nm, sizeof(t_nm));
		nm.curr_argv = argv[i];
		nm.bin_location = argv[0];
		if ((fd = open(argv[i], O_RDONLY)) != -1)
			ret = process(&nm, fd, nm_handle_mach_o, nm_handle_fat);
	}
	return (ret <= 0);
}
