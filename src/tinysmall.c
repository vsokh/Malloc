#include "malloc.h"

static void			init_zone(t_zone *zone)
{
	if (!zone || zone->blocks)
		return ;

	zone->blocks = alloc_mem(zone->free_space);

	t_meta_data *head = NULL;
	for (size_t head_idx = 0; head_idx < zone->heads_num; head_idx++)
	{
		head = head_at(zone, head_idx);
		head->next = head;
		head->prev = head;
		head->size = zone->block_size;
		head->inuse = 0;
	}
}

static void			split_block(t_meta_data *block, size_t new_size)
{
	t_meta_data *new_block = (void*)((char*)block + new_size);
	new_block->prev = block;
	new_block->next = block->next;
	new_block->inuse = 0;
	new_block->size = block->size - new_size;
	new_block->next->prev = new_block;

	block->next = new_block;
	block->size = new_size;
	block->inuse = 1;
}

static t_meta_data	*search_by_size(t_meta_data *head, size_t size)
{
	if (!head)
		return NULL;

	t_meta_data *block = head;
	do {

		if (!block->inuse && datasize(block) >= size - sizeof(t_meta_data))
			return block;

		block = block->next;
	} while (block != head);
	return NULL;
}

static void 		*try_alloc(t_zone *zone, size_t size)
{
	if (!zone)
		return NULL;
	if (zone->free_space < size)
		return NULL;

	t_meta_data *head = NULL;
	t_meta_data *curr = NULL;
	for (size_t head_idx = 0; head_idx < zone->heads_num; head_idx++)
	{
		head = head_at(zone, head_idx);
		curr = search_by_size(head, size);
		if (curr)
		{
			if (datasize(curr) > size)
				split_block(curr, size);
			curr->inuse = 1;
			zone->free_space -= curr->size;
			return block2mem(curr);
		}
	}
	return NULL;
}

void				*try_alloc_tinysmall_block(size_t size)
{
	void *mem = NULL;

	if (size <= TINY_BLOCK_SIZE)
	{
		init_zone(&g_zones[TINY]);
		mem = try_alloc(&g_zones[TINY], size);
	}
	if (!mem && size <= SMALL_BLOCK_SIZE)
	{
		init_zone(&g_zones[SMALL]);
		mem = try_alloc(&g_zones[SMALL], size);
	}
	return mem;
}

static void			merge_block(t_meta_data *head, t_meta_data *block)
{
	if ((block->prev == head || block->next == head) && block != head && !head->inuse)
	{
		block->inuse = 0;
		merge_block(head, head);
		return ;
	}

	if (block != block->prev && !block->prev->inuse)
	{
		size_t prev_size = block->prev->size;
		block->prev->prev->next = block;
		block->prev = block->prev->prev;
		block->size += prev_size;
	}
	if (block != block->next && !block->next->inuse)
	{
		size_t next_size = block->next->size;
		block->next->next->prev = block;
		block->next = block->next->next;
		block->size += next_size;
	}
	block->inuse = 0;
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

static int			try_free(t_zone *zone, void *ptr)
{
	if (!zone)
		return 0;

	t_meta_data *head = NULL;
	t_meta_data *curr = NULL;
	for (size_t head_idx = 0; head_idx < zone->heads_num; head_idx++)
	{
		head = head_at(zone, head_idx);
		curr = search_by_ptr(head, ptr);
		if (curr)
		{
			if (!curr->inuse)
				break ;

			zone->free_space += curr->size;
			merge_block(head, curr);
			return 1;
		}
	}
	return 0;
}

int					try_free_tinysmall_block(void *ptr)
{
	int success = try_free(&g_zones[TINY], ptr);
	if (success)
	{
		if (g_zones[TINY].free_space == TINY_ZONE_SIZE)
		{
			munmap(g_zones[TINY].blocks, g_zones[TINY].free_space);
			g_zones[TINY].blocks = NULL;
		}
		return success;
	}

	success = try_free(&g_zones[SMALL], ptr);
	if (success)
	{
		if (g_zones[SMALL].free_space == SMALL_ZONE_SIZE)
		{
			munmap(g_zones[SMALL].blocks, g_zones[SMALL].free_space);
			g_zones[SMALL].blocks = NULL;
		}
	}

	return success;
}

