/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:27:22 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/19 15:04:25 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_arena				g_arena;
pthread_mutex_t		g_mtx = PTHREAD_MUTEX_INITIALIZER;

int			alloc_mem(void **mem, size_t size)
{
	*mem = mmap(
			NULL, size,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS,
			-1, 0
	);
	return *mem == MAP_FAILED ? 1 : 0;
}

static int	try_alloc_mem(void **mem, size_t size)
{
	int err = try_alloc_tinysmall_block(mem, size);
	if (err)
		return err;
	if (*mem)
		return 0;

	err = try_alloc_large_block(mem, size);
	if (err)
		return err;
	return 0;
}

void		*malloc(size_t size)
{
	if (size == 0)
		return NULL;

	void *mem = NULL;
	if (pthread_mutex_lock(&g_mtx) == 0)
	{
		int err = try_alloc_mem(&mem, req2size(size));
		if (err || !mem)
			errno = ENOMEM;
		pthread_mutex_unlock(&g_mtx);
	}
	return mem;
}

