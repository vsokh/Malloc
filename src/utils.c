/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:17:21 by vsokolog          #+#    #+#             */
/*   Updated: 2021/03/15 18:29:54 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align4(size_t x)
{
	return ((((x - 1) >> 2) << 2) + 4);
}

void	print_constants(void)
{
	struct rlimit	*rlp;

	getrlimit(RLIMIT_DATA, rlp);
	printf("rlim_cur: %llu\n", rlp->rlim_cur);
	printf("rlim_max: %llu\n", rlp->rlim_max);
	printf("getpagesize: %d\n", getpagesize());
}

void	print_meta_block(t_meta_block *b)
{
	int i;

	printf("----------\n");
	printf("block_addr: %p\n", b);
	printf("size: %zd\n", b->size);
	printf("next: %p\n", b->next);
	printf("free: %d\n", b->free);
	printf("data: ");
	i = -1;
	while (++i < b->size)
		printf("%c", b->data[i]);
	printf("\n----------");
}
