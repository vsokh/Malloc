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

int					try_alloc_large_block(void **mem, size_t size)
{
	size_t pages = align2page(size);
	t_meta_data *block = NULL;
	int err = alloc_mem((void**)&block, pages);
	if (err)
		return err;

	block->inuse = 1;
	block->size = pages;
	add_block(&g_arena.large_zone, block);
	*mem = block2mem(block);

	return 0;
}


static void			remove_block(t_meta_data *block)
{
	if (!block)
		return ;

	block->prev->next = block->next;
	block->next->prev = block->prev;

	if (g_arena.large_zone == block)
	{
		if (block->next != block)
			g_arena.large_zone = block->next;
		else
			g_arena.large_zone = NULL;
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

int					try_free_large_block(void **ptr)
{
	t_meta_data *block = search_by_ptr(g_arena.large_zone, *ptr);
	if (block && !block->inuse)
		return 1;

	remove_block(block);
	munmap(block, block->size);
	*ptr = NULL;

	return 0;
}

