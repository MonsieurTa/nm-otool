/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 07:37:10 by wta               #+#    #+#             */
/*   Updated: 2020/02/16 17:05:17 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stddef.h>
#include "ft_printf.h"
#include "ft_nm.h"
#include "ft_otool.h"

int			g_bin = BIN_OTOOL;

int			main(int argc, char *argv[])
{
	t_nm		nm;
	int			fd;
	int			i;
	int			ret;

	if (argc == 1)
		return (0);
	i = 0;
	ret = 0;
	while (++i < argc)
	{
		ft_bzero(&nm, sizeof(t_nm));
		nm.curr_argv = argv[i];
		nm.bin_location = argv[0];
		if ((fd = open(argv[i], O_RDONLY)) != -1)
			ret |= process(&nm, fd, otool_handle_mach_o, otool_handle_fat);
	}
	return (ret == -1);
}
