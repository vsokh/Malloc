#include "malloc.h"

t_arena	g_arena;

void		*alloc(size_t size)
{
	void *mem = mmap(
		NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0
	);
	if (mem == MAP_FAILED)
		return (NULL);
	return mem;
}

void		add_block(t_block *block, size_t new_size)
{
	t_block *new_block = (void*)((char*)block + new_size);
	new_block->prev = block;
	new_block->next = block->next;
	new_block->inuse &= AVAIL;
	new_block->size = block->size - new_size;
	new_block->next->prev = new_block;

	block->next = new_block;
	block->size = new_size;
}

int			init_zone(t_slab *zone, size_t zone_size, size_t slab_size)
{
	void *zone_mem = alloc(zone_size);
	if (zone_mem == NULL)
		return 0;

	for (int slab_idx = 0; slab_idx < SLABS; slab_idx++) {
		void *slab_mem = (void*)((char*)zone_mem + slab_size * slab_idx);
		zone[slab_idx].blocks = slab_mem;
		zone[slab_idx].blocks->next = zone[slab_idx].blocks;
		zone[slab_idx].blocks->prev = zone[slab_idx].blocks;
	}
	return 1;
}

static void	*find_block(t_block *head, size_t block_size)
{
	t_block *block = head;
	do {
		if (!isinuse(block) && datasize(block) >= block_size - sizeof(t_block))
			return block;
		block = block->next;
	} while (block != head);
	return NULL;
}

void		*find_tinysmall_block(t_slab *zone, size_t zone_size, size_t slab_size, size_t block_size)
{
	if (zone[0].blocks == NULL) {
		if (!init_zone(zone, zone_size, slab_size))
			return NULL;
	}

	int slab_idx = 0;
	t_block *head = NULL;
	t_block *block = NULL;
	while (slab_idx < SLABS) {
		head = zone[slab_idx].blocks;
		block = find_block(head, block_size);

		if (block != NULL) {
			if (datasize(block) > block_size)
				add_block(block, block_size);
			block->inuse &= ~AVAIL;
			return block;
		}

		slab_idx++;
	}
	return NULL;
}

void		*allocate_large_block(size_t size)
{
	(void)size;
	return NULL;
}

void		*malloc(size_t size)
{
	size_t	block_size = size2blocksz(size);
	t_block	*block = NULL;

	if (block_size <= TINY_SLAB_SIZE) {
		block = find_tinysmall_block(
			g_arena.tiny_zone, TINY_ZONE_SIZE, TINY_SLAB_SIZE, block_size
		);
	}
	if (block == NULL && block_size <= SMALL_SLAB_SIZE) {
		block = find_tinysmall_block(
			g_arena.small_zone, SMALL_ZONE_SIZE, SMALL_SLAB_SIZE, block_size
		);
	}
	if (block == NULL) {
		block = allocate_large_block(block_size);
	}
	if (block == NULL) {
		errno = ENOMEM;
		return NULL;
	}
	return block2mem(block);
}

