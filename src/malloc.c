/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:58:13 by vsokh             #+#    #+#             */
/*   Updated: 2021/03/15 18:48:23 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta_block	*to_meta_block(void *ptr)
{
	size_t	shift;

	shift = sizeof(size_t) + sizeof(struct s_meta_block *) + sizeof(int);
	return (ptr - shift);
}

void			free(void *ptr)
{
	t_meta_block	*b;

	b = to_meta_block(ptr);
	print_meta_block(b);
}

void			malloc(size_t size)
{
	t_meta_block	*chunk;
	size_t			z;

	sz = align4(size) + sizeof(t_meta_block);
	chunk = mmap(NULL, sz,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
		0, 0);
	if (chunk == MAP_FAILED)
		return (NULL);
	chunk->size = sz;
	chunk->next = chunk;
	chunk->free = 25;
	return (chunk->data);
}

#ifdef DEBUG

int			main(void)
{
	char *p;
	char *h;

	p = malloc(5);
	h = "hello";
	memcpy(p, h, strlen(h));
	free(p);
	return (1);
}
#endif
