/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:49:57 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 18:08:20 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include <stddef.h>
#include "ft_printf.h"
#include "libft.h"
#include "nm.h"

char	g_archive_prefix[] = "!<arch>\n";

void	print_result(t_list *head)
{
	t_list	*node;

	node = head;
	while (node) {
		t_nm_result *res = (t_nm_result*)node->content;
		if (res->symchar != '-')
			ft_printf("%s %c %s\n", res->symaddr, res->symchar, res->symname);
		node = node->next;
	}
}

int		parse_mach_o(t_nm *nm)
{
	t_mach_o	*mach_o;

	mach_o = &nm->mach_o;
	mach_o->magic = *(uint32_t*)(mach_o->content);
	if (!get_mach_o_spec(mach_o))
		return (0);
	if (!handle_load_commands(nm))
		return (0);
	return (1);
}

int		cmp_addr(t_nm_result *a, t_nm_result *b)
{
	int32_t	name_diff;

	if ((name_diff = ft_strcmp(a->symname, b->symname)) == 0)
		return (ft_strcmp(a->symaddr, b->symaddr));
	return (name_diff);
}

int		handle_mach_o(t_nm *nm)
{
	parse_mach_o(nm);
	sort(&nm->mach_o.result, cmp_addr);
	print_result(nm->mach_o.result.head);
	return (1);
}

int		is_fat(uint32_t magic)
{
	return (magic == FAT_MAGIC || magic == FAT_CIGAM
	|| magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64);
}

int		handle_fat(t_nm *nm)
{
	t_fat_header	fat_header;
	uint32_t		magic;

	(void)fat_header;
	magic = *(uint32_t*)nm->content;
	if (is_fat(magic))
	{

	}
	else
		nm->mach_o.content = nm->content;
	return (1);
}

int		main(int argc, char *argv[])
{
	t_nm		nm;
	int			fd;
	int			i;

	if (argc == 1)
		return (0);
	i = 0;
	while (++i < argc)
	{
		ft_bzero(&nm, sizeof(nm));
		if ((fd = open(argv[i], O_RDONLY)) != -1)
		{
			fstat(fd, &nm.filestat);
			nm.content = mmap(NULL, nm.filestat.st_size,
				PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
			close(fd);
			handle_fat(&nm);
			handle_mach_o(&nm);
			munmap(nm.content, nm.filestat.st_size);
		}
	}
	return (0);
}
