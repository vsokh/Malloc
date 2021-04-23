/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:27:15 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/22 20:33:19 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_meta_data	*search_by_ptr(t_meta_data *head, void *ptr)
{
	if (!head)
		return NULL;

	t_meta_data *block = head;
	do {

		if (block2mem(block) == ptr)
			return block;

		block = block->next;
	} while (block != head);
	return NULL;
}

static t_meta_data	*search_in_zone(t_zone *zone, void *ptr)
{
	if (!zone)
		return NULL;

	t_meta_data *head = NULL;
	t_meta_data *block = NULL;
	for (size_t head_idx = 0; head_idx < zone->heads_num; head_idx++)
	{
		head = head_at(zone, head_idx);
		block = search_by_ptr(head, ptr);
		if (block)
			return block;
	}
	return NULL;
}

static void			*move_block(t_meta_data *block, size_t size)
{
	if (!block || !block->inuse)
		return NULL;

	void *src_ptr = block2mem(block);
	void *dst_ptr = src_ptr;
	if (datasize(block) < size)
	{
		dst_ptr = malloc(size);
		if (!dst_ptr)
			return NULL;

		size_t src_size = datasize(block);
		ft_memcpy(dst_ptr, src_ptr, src_size);
		free(src_ptr);
	}
	return dst_ptr;
}

void				*realloc(void *ptr, size_t size)
{
	if (!ptr || !size)
		return NULL;

	t_meta_data *block = NULL;
	if (pthread_mutex_lock(&g_mtx) == 0)
	{
		block = search_in_zone(&g_zones[TINY], ptr);
		if (!block)
			block = search_in_zone(&g_zones[SMALL], ptr);
		if (!block)
			block = search_in_zone(&g_zones[LARGE], ptr);
		pthread_mutex_unlock(&g_mtx);
	}
	return move_block(block, size);
}

