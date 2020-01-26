/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:49:57 by wta               #+#    #+#             */
/*   Updated: 2020/01/26 20:40:17 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
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
	nm->sizeofcmds = mach_header.sizeofcmds;
	if (is_64(nm->magic))
		nm->spec |= IS_64;
	if (is_swap(nm->magic))
		nm->spec |= IS_SWAP;
	return (1);
}

void	print_symbol_name(t_nm *nm, t_symtab_command *sym)
{
	char			*strtab;
	t_nlist_64		*nlist;
	uint32_t		offset;
	uint32_t		i;

	offset = (nm->spec & IS_64) ? sizeof(t_nlist_64) : sizeof(t_nlist);
	strtab = nm->content + sym->stroff;
	nlist = nm->content + sym->symoff;
	i = -1;
	while (++i < sym->nsyms)
	{
		ft_printf("%s\n", strtab + nlist->n_un.n_strx);
		nlist = (void*)nlist + offset;
	}
}

void	store_sections(t_nm *nm, void *ptr, uint32_t nsects)
{
	t_list		*node;
	uint32_t	offset;
	uint32_t	i;

	offset = nm->spec & IS_64 ? sizeof(t_section_64) : sizeof(t_section);
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
	uint32_t	is_64;
	uint32_t	offset;

	is_64 = nm->spec & IS_64;
	offset = is_64 ? sizeof(t_segment_command_64) : sizeof(t_segment_command);
	nsects = *(uint32_t*)(segment_command + offset - (sizeof(uint32_t) * 2));
	nm->nsects += nsects;
	store_sections(nm, segment_command + offset, nsects);
}

int		handle_load_command(t_nm *nm)
{
	t_load_command		*lc;
	t_symtab_command	*sym;
	uint32_t			i;

	lc = (void*)nm->content + nm->header_size;
	i = -1;
	while (++i < nm->ncmds)
	{
		if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
			handle_sections(nm, (void*)lc);
		else if (lc->cmd == LC_SYMTAB)
		{
			sym = (t_symtab_command*)(void*)lc;
			print_symbol_name(nm, sym);
			break ;
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
	while (i < argc)
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
		}
		i++;
	}
	return (0);
}
