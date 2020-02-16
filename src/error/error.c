/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:03:04 by wta               #+#    #+#             */
/*   Updated: 2020/02/16 16:14:49 by wta              ###   ########.fr       */
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
	ft_putstr_fd("truncated or malformed file\n", STDERR_FILENO);
	ft_putstr_fd(g_bin == BIN_NM ? "\n" : "", STDERR_FILENO);
}

static void	print_not_mach_o(t_nm *nm)
{
	ft_putstr_fd(nm->bin_location, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (nm->is_fat)
		ft_putstr_fd("Mach-O universal file: ", STDERR_FILENO);
	ft_putstr_fd(nm->curr_argv, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	ft_putstr_fd("The file was not recognized as a Mach-O file\n",
		STDERR_FILENO);
	ft_putstr_fd(g_bin == BIN_NM ? "\n" : "", STDERR_FILENO);
}

static void	print_not_valid(t_nm *nm)
{
	ft_putstr_fd(nm->bin_location, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(nm->curr_argv, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	ft_putstr_fd("The file was not recognized as a valid object file\n",
		STDERR_FILENO);
	ft_putstr_fd(g_bin == BIN_NM ? "\n" : "", STDERR_FILENO);
}

static void	print_no_such_file_or_dir(t_nm *nm)
{
	ft_putstr_fd(nm->bin_location, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(nm->curr_argv, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("No such file or directory.\n",
		STDERR_FILENO);
}

int			throw_error(t_nm *nm, int err_code)
{
	if (err_code == ERR_TRUNCATED_OR_MALFORMED)
		print_truncated_or_malformed_error(nm);
	if (err_code == ERR_NOT_MACH_O)
		print_not_mach_o(nm);
	if (err_code == ERR_NOT_VALID)
		print_not_valid(nm);
	if (err_code == ERR_NO_SUCH_FILE_OR_DIR)
		print_no_such_file_or_dir(nm);
	return (-1);
}
