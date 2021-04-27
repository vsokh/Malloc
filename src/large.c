/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:49:34 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/27 14:13:12 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			add_block(t_meta_data **head, t_meta_data *block)
{
	t_meta_data *tmp_head = *head;
	if (!tmp_head)
	{
		if (!block->next) block->next = block;
		if (!block->prev) block->prev = block;

		*head = block;
		return ;
	}

	tmp_head->prev->next = block;
	block->prev = tmp_head->prev;

	tmp_head->prev = block;
	block->next = tmp_head;
}

void				*try_alloc_large_block(size_t size)
{
	size_t pages = align2page(size);
	t_meta_data *block = alloc_mem(pages);
	if (!block)
		return NULL;

	block->inuse = 1;
	block->size = pages;
	add_block(&g_zones[LARGE].blocks, block);

	return block2mem(block);
}

static void			remove_block(t_meta_data *block)
{
	if (!block)
		return ;

	block->prev->next = block->next;
	block->next->prev = block->prev;

	if (g_zones[LARGE].blocks == block)
	{
		if (block->next != block)
			g_zones[LARGE].blocks = block->next;
		else
			g_zones[LARGE].blocks = NULL;
	}
}

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

void				try_free_large_block(void *ptr)
{
	t_meta_data *block = search_by_ptr(g_zones[LARGE].blocks, ptr);
	if (!block)
		return ;
	if (block && !block->inuse)
		return ;

	remove_block(block);
	munmap(block, block->size);
}

