/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:26:21 by wta               #+#    #+#             */
/*   Updated: 2020/02/16 15:07:46 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

typedef struct s_nm	t_nm;

int			otool_handle_mach_o(t_nm *nm);

int			otool_handle_fat(t_nm *nm);

int			handle_text_lc_command(t_nm *nm);

void		swap_section(void *ptr);

void		swap_section_64(void *ptr);

void		format_addr(t_mach_o *mach_o, char dst[], uint64_t addr);

void		hexdump_byte(char dst[], uint8_t value);

void		format_hexdump(char dst[], void *ptr, uint32_t len);

void		print_text_hexdump(t_nm *nm, void *ptr, void *end, uint64_t addr);

int			seek_text_section(t_nm *nm, void *ptr, uint32_t nsects);

int			has_text_section(t_nm *nm, void *ptr);

int			seek_text_lc_command(t_nm *nm);

#endif
