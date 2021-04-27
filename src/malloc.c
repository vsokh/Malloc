/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:27:22 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/27 13:49:27 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone				g_zones[ZONE_NUM] = {
	[TINY]  = {NULL, "TINY", TINY_BLOCK_SIZE, TINY_HEADS_NUM, TINY_ZONE_SIZE},
	[SMALL] = {NULL, "SMALL", SMALL_BLOCK_SIZE, SMALL_HEADS_NUM, SMALL_ZONE_SIZE},
	[LARGE] = {NULL, "LARGE", 0, LARGE_HEADS_NUM, 0}
};

pthread_mutex_t		g_mtx = PTHREAD_MUTEX_INITIALIZER;

void				*alloc_mem(size_t size)
{
	void *mem = mmap(
			NULL, size,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS,
			-1, 0
	);
	return mem == MAP_FAILED ? NULL : mem;
}

static void			*try_alloc_mem(size_t size)
{
	void *mem = try_alloc_tinysmall_block(size);
	if (mem)
		return mem;

	return try_alloc_large_block(size);
}

void				*malloc(size_t size)
{
	if (!size)
		return NULL;

	void *mem = NULL;
	if (pthread_mutex_lock(&g_mtx) == 0)
	{
		mem = try_alloc_mem(req2size(size));
		pthread_mutex_unlock(&g_mtx);
	}
	return mem;
}

