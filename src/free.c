/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:55:54 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/19 15:20:21 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	try_free_block(void *ptr)
{
	int err = try_free_tinysmall_block(&ptr);
	if (err)
		return err;
	if (ptr == NULL)
		return 0;

	if (!g_arena.large_zone)
		return 1;

	err = try_free_large_block(&ptr);
	if (err)
		return err;
	if (ptr != NULL)
		return 1;

	return 0;
}

void		free(void *ptr)
{
	if (pthread_mutex_lock(&g_mtx) == 0)
	{
		if (ptr)
		{
			int err = try_free_block(ptr);
			if (err)
				errno = ENOMEM;
		}
		pthread_mutex_unlock(&g_mtx);
	}
}

