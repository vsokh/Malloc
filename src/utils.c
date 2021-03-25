/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:17:21 by vsokolog          #+#    #+#             */
/*   Updated: 2021/03/25 15:36:40 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_block(t_block *p)
{
	printf("[%11p<-(%p)->%11p]: %c, S:%zu\n",
			p->prev, p, p->next, !p->inuse ? 'F' : 'A', p->size);
}

size_t		align4(size_t x)
{
	return ((((x - 1) >> 2) << 2) + 4);
}

size_t		align_to_page(size_t x)
{
	return (getpagesize() * (x / getpagesize() + 1));
}

void		show_mem(void)
{
	t_block	*p;
	int		i;

	i = 0;
	p = g_first;
	printf("====================================================\n");
	if (p == NULL)
		printf("EMPTY\n");
	while (p != NULL)
	{
		print_block(p);
		p = p->next;
		i++;
	}
	printf("====================================================\n");
}
