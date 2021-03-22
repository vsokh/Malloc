/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:55:26 by vsokolog          #+#    #+#             */
/*   Updated: 2021/03/22 14:43:32 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*g_first = NULL;
t_block	*g_last = NULL;

void	free(void *ptr)
{
	t_block *p;

	p = g_first;
	if (ptr == NULL)
		return ;
	while (p != NULL)
	{
		if ((void*)p + sizeof(t_block) == ptr)
		{
			if (p->prev == NULL)
				g_first = p->next;
			else
			{
				p->prev->next = p->next;
				munmap((void*)p + sizeof(t_block), p->size - sizeof(t_block));
			}
			return ;
		}
		p = p->next;
	}
}

void	*realloc(void *ptr, size_t size)
{
	return (NULL);
}

void	*malloc(size_t size)
{
	t_block *b;
	size_t	asize;

	asize = align4(size) + sizeof(t_block);
	b = NULL; /* TODO: Add search in cache */
	if (b == NULL)
		b = find_block(asize);
	if (b == NULL)
	{
		b = new_block(asize);
		add_block(b);
	}
	return (b == NULL ? NULL : (void *)b + sizeof(t_block));
}

#ifdef DEBUG

/*
** TODO:
** [] free;
** [] realloc;
** [] cache;
** [] tests
*/

int		main(void)
{
	const int	allocs = 3;
	void		*ptrs[allocs];
	int			bytes[allocs] = {10, 1, 6};

	printf("ALLOCATE: ");
	for (int i = 0; i < allocs; i++)
	{
		ptrs[i] = malloc(bytes[i]);
		printf("p%d(%db), ", i, bytes[i]);
	}
	printf("\n");
	show_mem();

	printf("\nFREE: p2 \n\n");
	free(ptrs[2]);
	show_mem();
	return (0);
}
#endif
