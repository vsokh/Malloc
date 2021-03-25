/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:32:10 by vsokolog          #+#    #+#             */
/*   Updated: 2021/03/25 15:09:30 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	merge_left_if_can(t_block *b)
{
	uintptr_t	lower_boundary;

	lower_boundary = (uintptr_t)b % getpagesize();
	if (lower_boundary == 0 || b->prev == NULL || b->prev->inuse != 0)
		return ;
	b->prev->size += b->size;
	b->prev->next = b->next;
	b->next->prev = b->prev;
}

static void	merge_right_if_can(t_block *b)
{
	uintptr_t	upper_boundary;

	upper_boundary = ((uintptr_t)b + b->size) % getpagesize();
	if (upper_boundary == 0 || b->next == NULL || b->next->inuse != 0)
		return ;
	b->size += b->next->size;
	b->next = b->next->next;
	if (b->next->next != NULL)
		b->next->next->prev = b;
}

static void	reclaim_if_can(t_block *b)
{
	if (b->size % getpagesize() == 0)
	{
		if (b->prev != NULL)
			b->prev->next = b->next;
		if (b->next != NULL)
			b->next->prev = b->prev;
		if (b->next == NULL && b->prev == NULL)
		{
			g_first = NULL;
			g_last = NULL;
		}
		munmap(b, b->size);
	}
}

void		free(void *ptr)
{
	t_block *b;

	if (ptr == NULL)
		return ;
	b = g_first;
	while (b != NULL)
	{
		if ((void *)b + sizeof(t_block) == ptr)
		{
			b->inuse = 0;
			merge_left_if_can(b);
			merge_right_if_can(b);
			reclaim_if_can(b);
			return ;
		}
		b = b->next;
	}
}
