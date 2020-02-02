/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:34:27 by wta               #+#    #+#             */
/*   Updated: 2020/02/02 18:40:19 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "nm.h"

static void	divide_list(t_list_info *list, t_list_info *front, t_list_info *back)
{
	uint32_t	mid;
	t_list		*node;
	t_list		*tmp;

	mid = list->size / 2;
	front->size = mid;
	back->size = list->size - mid;
	node = list->head;
	while (node && --mid)
		node = node->next;
	tmp = node;
	node = node->next;
	tmp->next = NULL;
	back->head = node;
	back->tail = list->tail;
	front->head = list->head;
	front->tail = tmp;
}

static void	apply_merge(t_list_info **list, t_list_info *a, t_list_info *b,
					int (*cmp)(t_nm_result*, t_nm_result*))
{
	t_nm_result	*a_result;
	t_nm_result	*b_result;
	uint32_t	len;

	ft_bzero(*list, sizeof(t_list_info));
	len = a->size + b->size;
	while (--len && a->head && b->head)
	{
		a_result = (t_nm_result*)a->head->content;
		b_result = (t_nm_result*)b->head->content;
		if (cmp(a_result, b_result) > 0)
			ft_pushback(*list, pop(b));
		else
			ft_pushback(*list, pop(a));
	}
	while (a->size)
		ft_pushback(*list, pop(a));
	while (b->size)
		ft_pushback(*list, pop(b));
}

static void	merge_list(t_list_info *list, t_list_info *a, t_list_info *b,
					int (*cmp)(t_nm_result*, t_nm_result*))
{
	if (a->size == 0)
		return ((void)(*list = *b));
	if (b->size == 0)
		return ((void)(*list = *a));
	apply_merge(&list, b, a, cmp);
}

static void	merge_sort(t_list_info *list, int (*cmp)(t_nm_result*, t_nm_result*))
{
	t_list_info	front;
	t_list_info	back;

	if (list->size <= 1)
		return;
	divide_list(list, &front, &back);
	merge_sort(&front, cmp);
	merge_sort(&back, cmp);
	merge_list(list, &front, &back, cmp);
}

void		sort(t_list_info *list, int (*cmp)(t_nm_result*, t_nm_result*))
{
	merge_sort(list, cmp);
}
