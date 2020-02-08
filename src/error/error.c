/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:03:04 by wta               #+#    #+#             */
/*   Updated: 2020/02/08 17:11:19 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_nm.h"

static void	print_truncated_or_malformed_error(t_nm *nm)
{
	ft_putstr_fd(nm->bin_location, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(nm->curr_argv, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	ft_putstr_fd("truncated or malformed fat file\n", STDERR_FILENO);
}

int			throw_error(t_nm *nm, int err_code)
{
	if (err_code == ERR_TRUNCATED_OR_MALFORMED)
		print_truncated_or_malformed_error(nm);
	return (0);
}
