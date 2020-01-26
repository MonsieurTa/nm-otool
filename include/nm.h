/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:45:27 by wta               #+#    #+#             */
/*   Updated: 2020/01/26 20:14:52 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include "libft.h"

# define IS_SWAP	0x1
# define IS_64		0x2

typedef struct stat					t_stat;

typedef struct mach_header			t_mach_header;
typedef struct mach_header_64		t_mach_header_64;
typedef struct fat_header			t_fat_header;
typedef struct fat_arch				t_fat_arch;
typedef struct fat_arch_64			t_fat_arch_64;

typedef struct load_command			t_load_command;
typedef struct symtab_command		t_symtab_command;
typedef struct nlist_64				t_nlist_64;
typedef struct nlist				t_nlist;

typedef struct segment_command		t_segment_command;
typedef struct segment_command_64	t_segment_command_64;

typedef struct section				t_section;
typedef struct section_64			t_section_64;

typedef struct			s_nm
{
	void				*content;
	t_list_info			sections;

	uint32_t			magic;
	uint32_t			spec;
	uint32_t			header_size;
	uint32_t			ncmds;
	uint32_t			sizeofcmds;

	uint32_t			nsects;
}						t_nm;

uint32_t				byte_swap32(uint32_t x);
uint64_t				byte_swap64(uint64_t x);

#endif
