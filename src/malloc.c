/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:39:49 by vsokolog          #+#    #+#             */
/*   Updated: 2021/03/25 18:39:50 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*g_first = NULL;
t_block	*g_last = NULL;

/*
**	Description:
**		Splits one block up to two,
**		where the first is allocated and the second is freed.
**	Params:
**		new_size - size for the allocated block.
*/

static t_block	*split_block(t_block *b, size_t new_size)
{
	t_block	*f;

	f = (void *)b + new_size;
	f->prev = b;
	f->next = b->next;
	f->inuse = 0;
	f->size = b->size - new_size;
	b->next = f;
	b->size = new_size;
	return (b);
}

static void		add_block(t_block *b)
{
	if (g_first == NULL)
		g_first = b;
	else
	{
		g_last->next = b;
		b->prev = g_last;
	}
	g_last = b->next == NULL ? b : b->next;
}

static t_block	*find_block(size_t size)
{
	t_block *b;

	b = g_first;
	while (b != NULL)
	{
		if (b->inuse == 0 && b->size >= size)
		{
			b->inuse = 1;
			break ;
		}
		b = b->next;
	}
	return (b);
}

static t_block	*new_block(size_t size)
{
	t_block		*b;
	size_t		apsize;

	apsize = align_to_page(size + sizeof(t_block));
	b = mmap(NULL, apsize,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
		-1, 0);
	if (b == MAP_FAILED)
		return (NULL);
	b->prev = NULL;
	b->next = NULL;
	b->inuse = 1;
	b->size = apsize;
	return (b);
}

void		*malloc(size_t size)
{
	t_block *b;
	size_t	asize;

	asize = align4(size) + sizeof(t_block);
	b = NULL;
	if (b == NULL)
		b = find_block(asize);
	if (b == NULL)
		b = new_block(asize);
	if (b == NULL)
		return (NULL);
	if (b->size > asize)
		b = split_block(b, asize);
	add_block(b);
	return ((void *)b + sizeof(t_block));
}
