/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:49:34 by vsokolog          #+#    #+#             */
/*   Updated: 2021/07/18 15:19:27 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				print_block(t_meta_data *b)
{
	ft_putstr("prev: ");
	ft_putnbr16((uintptr_t)b->prev);
	ft_putstr(", ");
	ft_putnbr16((uintptr_t)b);
	ft_putstr(", next: ");
	ft_putnbr16((uintptr_t)b->next);
	ft_putstr(", size: ");
	ft_putnbr(b->size);
	ft_putstr(", flags: ");
	ft_putnbr(b->flags);
	ft_putstr("\n");
}

static t_meta_data	*merge_block(t_meta_data *block)
{
	t_meta_data *p = block->prev;
	t_meta_data *n = block->next;
	if (!is_inuse(p) && !(p->flags & IS_LAST) && p != n)
	{
		p->next = block->next;
		block->next->prev = p;
		p->size = block->size + p->size;
		p->flags |= block->flags;
		block = p;
	}
	if (!is_inuse(n) && !(n->flags & IS_FIRST))
	{
		block->next = n->next;
		block->next->prev = block;
		block->flags |= n->flags;
		block->size = block->size + n->size;
	}
	return block;
}

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

	t_meta_data *btail = block->prev;
	t_meta_data *htail = tmp_head->prev;

	block->prev = htail;
	htail->next = block;

	btail->next = tmp_head;
	tmp_head->prev = btail;
}


static void			split_block(t_meta_data *block, size_t size)
{
	t_meta_data *new_block = (void*)((char*)block + size);
	new_block->size = block->size - size;
	new_block->prev = block;
	new_block->next = block->next;
	new_block->flags |= block->flags;
	new_block->flags &= ~IS_FIRST;

	block->next->prev = new_block;
	block->next = new_block;
	block->size = size;
	block->flags &= ~IS_LAST;
}

t_meta_data			*find_block(t_zone *zone, size_t size)
{
	t_meta_data *head = zone->blocks;
	if (!head)
		return NULL;
	t_meta_data *block = head;
	do
	{
		if (!is_inuse(block) && block->size >= size)
		{
			if (datasize(block) > size)
				split_block(block, size);
			block->flags |= IS_INUSE;
			return block;
		}
		block = block->next;
	} while (head != block);
	return NULL;
}

t_meta_data			*new_block(t_zone *zone, size_t size)
{
	size_t pagesz = align2page(size);
	t_meta_data *block = alloc_mem(pagesz);
	if (!block)
		return NULL;
	block->size = pagesz;
	block->prev = block;
	block->next = block;
	block->flags = IS_FIRST | IS_LAST;
	if (datasize(block) > size)
		split_block(block, size);
	block->flags |= IS_INUSE;
	add_block(&zone->blocks, block);
	return block;
}

void				*try_alloc_large_block(size_t size)
{
	t_meta_data *block = find_block(&g_zones[LARGE], size);
	if (block)
		return block2mem(block);

	block = new_block(&g_zones[LARGE], size);
	if (block)
		return block2mem(block);
	return NULL;
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
static int			remove_block(t_meta_data *block)
{
	if (!block)
		return 0;
	if (!(is_last(block) && is_first(block)))
		return 0;

	block->prev->next = block->next;
	block->next->prev = block->prev;

	if (g_zones[LARGE].blocks == block)
	{
		if (block->next != block)
			g_zones[LARGE].blocks = block->next;
		else
			g_zones[LARGE].blocks = NULL;
	}
	return 1;
}


#include <unistd.h>

void				try_free_large_block(void *ptr)
{
	t_meta_data *block = search_by_ptr(g_zones[LARGE].blocks, ptr);
	if (!block)
		return ;
	if (block && !is_inuse(block))
		return ;

	block->flags &= ~IS_INUSE;
	block = merge_block(block);
	void *addr = block;
	size_t size = block->size;
	if (remove_block(block)) {
		munmap(addr, size);
	}
}

