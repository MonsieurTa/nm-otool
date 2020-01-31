/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:49:57 by wta               #+#    #+#             */
/*   Updated: 2020/01/31 19:47:22 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stddef.h>
#include "ft_printf.h"
#include "libft.h"
#include "nm.h"

char	g_archive_prefix[] = "!<arch>\n";

int		is_32(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM);
}

int		is_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

int		get_header_size(t_nm *nm)
{
	if (is_32(nm->magic))
		return ((nm->header_size = sizeof(t_mach_header)) != 0);
	else if (is_64(nm->magic))
		return ((nm->header_size = sizeof(t_mach_header_64)) != 0);
	return (0);
}

int		is_swap(uint32_t magic)
{
	return (magic == MH_CIGAM || magic == MH_CIGAM_64);
}

int		get_spec(t_nm *nm)
{
	t_mach_header_64	mach_header;

	ft_bzero(&mach_header, sizeof(t_mach_header_64));
	if (!get_header_size(nm))
		return (0);
	ft_memcpy((void *)&mach_header, nm->content, nm->header_size);
	nm->ncmds = mach_header.ncmds;
	nm->is_64 = is_64(nm->magic);
	nm->is_swap = is_swap(nm->magic);
	nm->nlist_size = nm->is_64 ? sizeof(t_nlist_64) : sizeof(t_nlist);
	nm->section_size = nm->is_64 ? sizeof(t_section_64) : sizeof(t_section);
	nm->segment_size = nm->is_64 ? sizeof(t_segment_command_64) : sizeof(t_segment_command);
	return (1);
}

void	*find_section(t_list_info *sections, void *nlist)
{
	t_list		*node;
	uint8_t		index;
	uint32_t	i;

	index = *(uint8_t*)(nlist + offsetof(t_nlist_64, n_sect)) - 1;
	if (index >= sections->size)
		return (NULL);
	node = sections->head;
	i = -1;
	while (++i < index)
		node = node->next;
	return (node->content);
}

uint8_t	match_symbol_section(t_nm *nm, void *nlist, uint8_t n_type)
{
	char	*sectname;
	void	*section;
	char	c;

	section = find_section(&nm->sections, nlist);
	if (!section)
		return (0);
	sectname = (char*)(section + offsetof(t_section_64, sectname));
	if (ft_strequ(sectname, SECT_TEXT))
		c = 'T';
	else if (ft_strequ(sectname, SECT_DATA))
		c = 'D';
	else if (ft_strequ(sectname, SECT_TEXT))
		c = 'T';
	else
		c = 'S';
	if (!(n_type & N_EXT))
		c -= 'A' - 'a';
	return (c);
}

uint8_t	get_symbol_letter(t_nm *nm, void *nlist)
{
	uint8_t	n_type;

	n_type = *(uint8_t*)(nlist + sizeof(uint32_t));
	if (n_type & N_STAB)
		return '-';
	else if ((n_type & N_TYPE) == N_UNDF)
	{
		if (n_type & N_EXT)
			return 'U';
	}
	else if ((n_type & N_TYPE) == N_SECT)
		return match_symbol_section(nm, nlist, n_type);
	else if ((n_type & N_TYPE) == N_ABS)
		return 'A';
	else if ((n_type & N_TYPE) == N_INDR)
		return 'I';
	return (0);
}

void	format_symaddr(char dst[], uint64_t addr)
{
	static const char	base[] = "0123456789abcdef";
	uint32_t			i;

	ft_strcpy(dst, "0000000000000000");
	i = 16;
	while (--i && addr)
	{
		dst[i] = base[addr % 16];
		addr /= 16;
	}
}

void	push_result(t_nm *nm, uint64_t addr, uint8_t c, char *str)
{
	t_nm_result	node_content;
	t_list		*node;

	ft_bzero(&node_content, sizeof(t_nm_result));
	format_symaddr(node_content.symaddr, addr);
	node_content.symchar = c;
	node_content.symname = ft_strdup(str);
	node = ft_lstnew(&node_content, sizeof(t_nm_result));
	ft_pushback(&nm->result, node);
}

void	handle_symbol(t_nm *nm, void *nlist)
{
	uint64_t	n_value;
	uint8_t		n_value_size;
	uint8_t		offset;
	uint8_t 	c;
	char		*symname;

	offset = nm->is_64 ? offsetof(t_nlist_64, n_value) : offsetof(t_nlist, n_value);
	n_value_size = nm->is_64 ? sizeof(uint64_t) : sizeof(uint32_t);
	ft_memcpy(&n_value, nlist + offset, n_value_size);
	c = get_symbol_letter(nm, nlist);
	symname = nm->strtab + *(uint32_t*)nlist;
	push_result(nm, n_value, c, symname);
}

void	handle_symtab(t_nm *nm, t_symtab_command *sym)
{
	void		*nlist;
	uint32_t	offset;
	uint32_t	i;

	offset = nm->nlist_size;
	nlist = nm->content + sym->symoff;
	nm->strtab = nm->content + sym->stroff;
	nm->strtabsize = sym->strsize;
	i = -1;
	while (++i < sym->nsyms)
	{
		handle_symbol(nm, nlist);
		nlist = (void*)nlist + offset;
	}
}

void	store_sections(t_nm *nm, void *ptr, uint32_t nsects)
{
	t_list		*node;
	uint32_t	offset;
	uint32_t	i;

	offset = nm->section_size;
	i = -1;
	while (++i < nsects)
	{
		node = ft_lstnew_mallocfree(ptr, (size_t)offset);
		ft_pushback(&nm->sections, node);
		ptr += offset;
	}
}

void	handle_sections(t_nm *nm, void *segment_command)
{
	uint32_t	nsects;
	uint32_t	offset;

	offset = nm->is_64 ? offsetof(t_segment_command_64, nsects) : offsetof(t_segment_command, nsects);
	nsects = *(uint32_t*)(segment_command + offset);
	nm->nsects += nsects;
	store_sections(nm, segment_command + nm->segment_size, nsects);
}

int		handle_load_command(t_nm *nm)
{
	t_load_command			*lc;
	t_symtab_command		*sym;
	uint32_t				i;

	lc = (void*)nm->content + nm->header_size;
	i = -1;
	while (++i < nm->ncmds)
	{
		if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
			handle_sections(nm, (void*)lc);
		else if (lc->cmd == LC_SYMTAB)
		{
			sym = (t_symtab_command*)(void*)lc;
			handle_symtab(nm, sym);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (1);
}

int		nm_start(t_nm *nm)
{
	nm->magic = *(uint32_t*)(nm->content);
	if (!get_spec(nm))
		return (0);
	if (!handle_load_command(nm))
		return (0);
	return (1);
}

int		main(int argc, char *argv[])
{
	t_stat	filestat;
	t_nm	nm;
	int		fd;
	int		i;

	if (argc == 1)
		return (0);
	i = 0;
	while (++i < argc)
	{
		ft_bzero(&nm, sizeof(nm));
		if ((fd = open(argv[i], O_RDONLY)) != -1)
		{
			fstat(fd, &filestat);
			nm.content = mmap(NULL, filestat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
			close(fd);
			if (filestat.st_size >= 4)
				nm_start(&nm);
			munmap(nm.content, filestat.st_size);

			t_list *node = nm.result.head;
			while (node) {
				t_nm_result *res = (t_nm_result*)node->content;
				if (res->symchar != '-')
					ft_printf("%s %c %s\n", res->symaddr, res->symchar, res->symname);
				node = node->next;
			}
		}
	}
	return (0);
}
