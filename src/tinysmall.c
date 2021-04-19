#include "malloc.h"

static int			new_zone(t_zone **zone, size_t zone_size, size_t block_size, size_t block_num)
{
	int err = alloc_mem((void**)zone, zone_size);
	if (err)
		return err;

	t_zone *tmp_zone = *zone;
	tmp_zone->block_size = block_size;
	tmp_zone->block_num = block_num;

	t_meta_data *head = NULL;
	for (size_t block_idx = 0; block_idx < tmp_zone->block_num; block_idx++)
	{
		head = block_head_at(tmp_zone, block_idx);
		head->next = head;
		head->prev = head;
		head->size = tmp_zone->block_size;
		head->inuse = 0;
	}
	return 0;
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

static t_meta_data 	*try_alloc(t_zone *zone, size_t size)
{
	if (!zone)
		return NULL;

	t_meta_data *head = NULL;
	t_meta_data *curr = NULL;
	for (size_t block_idx = 0; block_idx < zone->block_num; block_idx++)
	{
		head = block_head_at(zone, block_idx);
		curr = search_by_size(head, size);
		if (curr)
		{
			if (datasize(curr) > size)
				split_block(curr, size);
			curr->inuse = 1;
			return curr;
		}
	}
	return NULL;
}

int					try_alloc_tinysmall_block(void **mem, size_t size)
{
	int err = 0;
	if (!g_arena.tiny_zone)
		err = new_zone(&g_arena.tiny_zone, TINY_ZONE_SIZE, TINY_BLOCK_SIZE, TINY_BLOCKS_NUM);
	if (err)
		return err;

	t_meta_data *block = try_alloc(g_arena.tiny_zone, size);
	if (block)
	{
		*mem = block2mem(block);
		return 0;
	}

	if (!g_arena.small_zone)
		err = new_zone(&g_arena.small_zone, SMALL_ZONE_SIZE, SMALL_BLOCK_SIZE, SMALL_BLOCKS_NUM);
	if (err)
		return err;

	block = try_alloc(g_arena.small_zone, size);
	if (block)
		*mem = block2mem(block);

	return 0;
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

static int			try_free(t_zone *zone, void **ptr)
{
	if (!zone)
		return 0;

	t_meta_data *head = NULL;
	t_meta_data *curr = NULL;
	for (size_t block_idx = 0; block_idx < zone->block_num; block_idx++)
	{
		head = block_head_at(zone, block_idx);
		curr = search_by_ptr(head, *ptr);
		if (curr)
		{
			if (!curr->inuse)
				return 1;

			merge_block(head, curr);
			*ptr = NULL;
			break ;
		}
	}
	return 0;
}

int					try_free_tinysmall_block(void **ptr)
{
	int err = try_free(g_arena.tiny_zone, ptr);
	if (err)
		return err;
	return try_free(g_arena.small_zone, ptr);
}

