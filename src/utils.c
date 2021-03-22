/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:17:21 by vsokolog          #+#    #+#             */
/*   Updated: 2021/03/22 14:07:30 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align4(size_t x)
{
	return ((((x - 1) >> 2) << 2) + 4);
}

void	show_mem(void)
{
	t_block *p = g_first;
	int i = 0;
	while (p != NULL)
	{
		printf("B[%1d]: M:%p, %c, S:%zu\n", i, p, !p->inuse ? 'F':'A', p->size);
		p = p->next;
		i++;
	}
}

