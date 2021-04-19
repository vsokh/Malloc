/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:27:08 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/19 15:55:09 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		print_block(t_meta_data *block)
{
	if (!block)
		return ;

	printf("%p<-%p->%p:%zu:%zu\n",
			block->prev, block, block->next, block->inuse, block->size);
}

void		print_blocks(t_meta_data *head, size_t *bytes)
{
	if (!head)
		return ;

	t_meta_data *block = head;
	do {
		if (block->inuse)
		{
			printf("%p - %p : %zu\n", block2mem(block), (void*)((char*)block2mem(block) + datasize(block)), datasize(block));
			*bytes += datasize(block);
		}

		block = block->next;
	} while (block != head);
}

void		print_zone(t_zone *zone, char *zone_name, size_t *bytes)
{
	if (!zone)
		return ;

	printf("%s : %p\n", zone_name, zone);
	t_meta_data *head = NULL;
	for (size_t block_idx = 0; block_idx < zone->block_num; block_idx++)
	{
		head = block_head_at(zone, block_idx);
		print_blocks(head, bytes);
	}
}

void		show_alloc_mem(void)
{
	size_t bytes = 0;
	print_zone(g_arena.tiny_zone, "TINY", &bytes);
	print_zone(g_arena.small_zone, "SMALL", &bytes);
	if (g_arena.large_zone)
	{
		printf("%s : %p\n", "LARGE", g_arena.large_zone);
		print_blocks(g_arena.large_zone, &bytes);
	}
	if (bytes > 0)
		printf("Total : %zu\n", bytes);
}

