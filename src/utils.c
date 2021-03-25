/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:17:21 by vsokolog          #+#    #+#             */
/*   Updated: 2021/03/25 13:02:52 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align4(size_t x)
{
	return ((((x - 1) >> 2) << 2) + 4);
}

size_t	align_to_page(size_t x)
{
	return (getpagesize() * (x / getpagesize() + 1));
}

void	print_block(t_block *p)
{
	printf("[%11p<-(%p)->%11p]: %c, S:%zu\n", p->prev, p, p->next, !p->inuse ? 'F':'A', p->size);
}

void	show_mem(void)
{
	t_block *p = g_first;
	int i = 0;
	printf("====================================================\n");
	if (p==NULL) { printf("EMPTY\n"); }
	while (p != NULL)
	{
		print_block(p);
		p = p->next;
		i++;
	}
	printf("====================================================\n");
}

