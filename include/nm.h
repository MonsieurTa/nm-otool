/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:45:27 by wta               #+#    #+#             */
/*   Updated: 2020/02/01 11:42:01 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <sys/stat.h>
# include "libft.h"

# define IS_SWAP	0x1
# define IS_64		0x2

typedef struct stat						t_stat;

typedef struct mach_header				t_mach_header;
typedef struct mach_header_64			t_mach_header_64;
typedef struct fat_header				t_fat_header;
typedef struct fat_arch					t_fat_arch;
typedef struct fat_arch_64				t_fat_arch_64;

typedef struct load_command				t_load_command;
typedef struct symtab_command			t_symtab_command;
typedef struct nlist_64					t_nlist_64;
typedef struct nlist					t_nlist;

typedef struct linkedit_data_command	t_linkedit_data_command;
typedef struct data_in_code_entry		t_data_in_code_entry;

typedef struct segment_command			t_segment_command;
typedef struct segment_command_64		t_segment_command_64;

typedef struct section					t_section;
typedef struct section_64				t_section_64;

typedef struct			s_nm_result
{
	char				*symname;
	char				symaddr[17];
	char				symchar;
}						t_nm_result;

typedef struct			s_nm
{
	t_stat				filestat;

	void				*content;
	t_list_info			sections;

	t_list_info			result;

	uint32_t			magic;

	uint8_t				is_64;
	uint8_t				is_swap;

	uint8_t				nlist_size;
	uint8_t				section_size;
	uint8_t				segment_size;
	uint8_t				header_size;

	uint32_t			ncmds;

	char				*strtab;
	uint32_t			strtabsize;

	uint32_t			nsects;
}						t_nm;

uint32_t				byte_swap32(uint32_t x);
uint64_t				byte_swap64(uint64_t x);

int						get_header_size(t_nm *nm);

int						get_spec_from_magic(t_nm *nm);

void					handle_sections(t_nm *nm, void *segment_command);
void					store_sections(t_nm *nm, void *ptr, uint32_t nsects);
void					*find_section(t_list_info *sections, void *nlist);

int						handle_symtab(t_nm *nm, t_symtab_command *sym);
int						handle_symbol(t_nm *nm, void *nlist);
uint8_t					get_symbol_letter(t_nm *nm, void *nlist);
uint8_t					match_symbol_section(
							t_nm *nm,
							void *nlist,
							uint8_t n_type);

int						handle_load_commands(t_nm *nm);

int						is_32(uint32_t magic);
int						is_64(uint32_t magic);
int						is_swap(uint32_t magic);

int						ptr_valid_range(void *start, uint32_t length, void *ptr);


void					format_symaddr(char c, char dst[], uint64_t addr);

void					push_result(
							t_nm *nm,
							uint64_t addr,
							uint8_t c,
							char *str);

#endif
