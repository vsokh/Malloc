/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:07:53 by vsokolog          #+#    #+#             */
/*   Updated: 2021/03/22 14:38:58 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	Description:
**		Splits one block up to two,
**		where the first is allocated and the second is freed.
**	Params:
**		new_size - size for the allocated block.
*/

void		split_block(t_block *b, size_t new_size)
{
	t_block	*f;

	f = (void *)b + new_size;
	f->prev = b;
	f->next = b->next;
	f->inuse = 0;
	f->size = b->size - new_size;
	b->next = f;
	b->size = new_size;
}

void		add_block(t_block *b)
{
	if (g_first == NULL)
	{
		g_first = b;
		g_last = b;
	}
	else
	{
		g_last->prev = g_last;
		g_last = b;
		g_last->next = NULL;
	}
}

t_block		*find_block(size_t size)
{
	t_block *b;

	b = g_first;
	while (b != NULL)
	{
		if (b->inuse == 0 && b->size >= size)
		{
			b->inuse = 1;
			if (b->size > size)
				split_block(b, size);
			return (b);
		}
		b = b->next;
	}
	return (NULL);
}

static int	align_to_page(size_t size)
{
	return (getpagesize() * (size / getpagesize() + 1));
}

t_block		*new_block(size_t size)
{
	t_block		*b;
	size_t		apsize;

	apsize = align_to_page(size);
	b = mmap(NULL, apsize,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
		0, 0);
	if (b == MAP_FAILED)
		return (NULL);
	b->prev = NULL;
	b->next = NULL;
	b->inuse = 1;
	b->size = apsize;
	if (apsize - size)
		split_block(b, size);
	return (b);
}
