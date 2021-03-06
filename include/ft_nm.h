/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:25:53 by wta               #+#    #+#             */
/*   Updated: 2020/02/16 16:06:33 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <mach/machine.h>
# include <sys/stat.h>
# include "libft.h"

# define IS_SWAP					0x1
# define IS_64						0x2

# define ERR_TRUNCATED_OR_MALFORMED	1
# define ERR_NOT_MACH_O				2
# define ERR_NOT_VALID				3
# define ERR_NO_SUCH_FILE_OR_DIR	4

# define BIN_NM						1
# define BIN_OTOOL					2

typedef struct stat						t_stat;

typedef struct fat_header				t_fat_header;
typedef struct fat_arch					t_fat_arch;
typedef struct fat_arch_64				t_fat_arch_64;

typedef struct mach_header				t_mach_header;
typedef struct mach_header_64			t_mach_header_64;

typedef struct load_command				t_load_command;
typedef struct symtab_command			t_symtab_command;
typedef struct nlist_64					t_nlist_64;
typedef struct nlist					t_nlist;

typedef struct segment_command			t_segment_command;
typedef struct segment_command_64		t_segment_command_64;

typedef struct section					t_section;
typedef struct section_64				t_section_64;

extern int		g_bin;
extern char		*(*g_dispatchers[])(cpu_subtype_t);

typedef struct			s_nm_result
{
	char	*symname;
	char	symaddr[17];
	char	symchar;
}						t_nm_result;

typedef struct			s_mach_o
{
	void			*content;

	t_list_info		sections;

	t_list_info		result;

	uint32_t		magic;

	uint8_t			is_64;
	uint8_t			is_cigam;

	uint8_t			nlist_size;
	uint8_t			section_size;
	uint8_t			segment_size;
	uint8_t			header_size;

	uint32_t		ncmds;

	char			*strtab;
	uint32_t		strtabsize;

	uint32_t		nsects;
}						t_mach_o;

typedef struct			s_fat
{
	t_fat_header		fat_header;

	uint8_t				is_64;
	uint8_t				is_cigam;

	cpu_type_t			cputype;
	cpu_subtype_t		cpusubtype;

	void				*fat_arch_struct;
	uint32_t			fat_arch_size;
	uint64_t			mach_o_size;
	uint64_t			offset_to_mach_o;
}						t_fat;

typedef struct			s_nm
{
	t_fat			fat;
	t_mach_o		mach_o;

	void			*section;

	t_stat			filestat;
	void			*content;
	char			*bin_location;
	char			*curr_argv;
	int				found_host_arch;
	int				is_fat;
}						t_nm;

int						process(
							t_nm *nm,
							int fd,
							int (*mach_o_handler)(t_nm*),
							int (*fat_handler)(t_nm*));

uint32_t				byte_swap32(uint32_t x);
uint64_t				byte_swap64(uint64_t x);
void					range_swap32(void *start, uint32_t len);
void					range_swap64(void *start, uint32_t len);
void					nlist_swap(t_nm *nm, void *nlist);
void					swap_fat_arch(void *ptr);
void					swap_fat_arch_64(void *ptr);

int						cmp_addr(t_nm_result *a, t_nm_result *b);

int						find_host_arch(t_nm *nm);

int						process_fat(t_nm *nm, int (*mach_o_handler)(t_nm*));

int						nm_handle_fat(t_nm *nm);
int						nm_handle_mach_o(t_nm *nm);
int						handle_fat_arch_struct(
							t_nm *nm,
							int (*mach_o_handler)(t_nm*));

char					*sarchitecture(t_nm *nm);

int						get_mach_o_header_size(t_nm *nm);

void					get_fat_spec(t_nm *nm);
int						get_mach_o_spec(t_nm *nm);

void					get_offsets(t_nm *nm, void *ptr);

void					handle_sections(
							t_nm *nm,
							void *segment_command);
void					*find_section(t_list_info *sections, void *nlist);

int						handle_symtab(t_nm *nm, t_symtab_command *sym);

int						handle_load_commands(t_nm *nm);

int						is_32(uint32_t magic);
int						is_64(uint32_t magic);
int						is_cigam(uint32_t magic);
int						is_fat(uint32_t magic);

int						ptr_valid_range(
							void *start,
							uint32_t length,
							void *ptr);

void					format_symaddr(
							t_mach_o *mach_o,
							char c,
							char dst[],
							uint64_t addr);

void					print_result(t_nm *nm);

void					push_result(
							t_nm *nm,
							uint64_t addr,
							uint8_t c,
							char *str);
void					rm_list(t_list_info *list);

t_list					*pop(t_list_info *list);
void					sort(
							t_list_info *list,
							int (*cmp)(t_nm_result*, t_nm_result*));

char					*vax(cpu_subtype_t subtype);
char					*mc680(cpu_subtype_t subtype);
char					*x86(cpu_subtype_t subtype);
char					*mc98000(cpu_subtype_t subtype);
char					*hppa(cpu_subtype_t subtype);
char					*arm(cpu_subtype_t subtype);
char					*mc88000(cpu_subtype_t subtype);
char					*sparc(cpu_subtype_t subtype);
char					*i860(cpu_subtype_t subtype);
char					*ppc(cpu_subtype_t subtype);

int						throw_error(t_nm *nm, int err_code);

#endif
