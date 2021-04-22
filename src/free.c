/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:55:54 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/22 13:34:42 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	try_free_block(void *ptr)
{
	int success = try_free_tinysmall_block(ptr);
	if (success)
		return ;

	try_free_large_block(ptr);
}

void		free(void *ptr)
{
	if (!ptr)
		return ;

	if (pthread_mutex_lock(&g_mtx) == 0)
	{
		try_free_block(ptr);
		pthread_mutex_unlock(&g_mtx);
	}
}
