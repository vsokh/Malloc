/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:27:08 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/22 16:27:08 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		ft_putchar(char c)
{
	write(1, &c, 1);
}

static void		ft_putnbr(size_t n)
{
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

static void		ft_putstr(char const *s)
{
	if (s == NULL)
		return ;
	int len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

static void		ft_putnbr16(unsigned long long n)
{
	const char *pref = "0x";
	int b = 16;
	int k = b;
	char a[b];
	char r = 0;
	while (n)
	{
		r = n % b;
		n /= b;
		if (r >= 10 && r <= 15)
			a[--k] = 'A' + r%10;
		else if (r <= 9)
			a[--k] = '0' + r;
	}
	write(1, pref, 2);
	if (k == b)
		write(1, pref, 1);
	else
		write(1, &a[k], b-k);
}

static size_t	print_blocks(t_meta_data *head)
{
	if (!head)
		return 0;

	size_t bytes = 0;
	t_meta_data *block = head;
	do {
		if (block->inuse)
		{
			uintptr_t start = (uintptr_t)block2mem(block);
			uintptr_t end = (uintptr_t)(void*)((char*)block2mem(block) + datasize(block));
			uintptr_t allocated = datasize(block);
			ft_putnbr16(start);
			ft_putstr(" - ");
			ft_putnbr16(end);
			ft_putstr(" : ");
			ft_putnbr(allocated);
			ft_putstr("\n");
			bytes += datasize(block);
		}
		block = block->next;
	} while (block != head);
	return bytes;
}

static void		print_head(t_zone *zone)
{
	ft_putstr(zone->name);
	ft_putstr(" : ");
	ft_putnbr16((uintptr_t)zone->blocks);
	ft_putstr("\n");
}

static size_t	print_zone(t_zone *zone)
{
	if (!zone)
		return 0;

	size_t bytes = 0;
	t_meta_data *head = NULL;
	for (size_t head_idx = 0; head_idx < zone->heads_num; head_idx++)
	{
		head = head_at(zone, head_idx);
		bytes += print_blocks(head);
	}
	return bytes;
}

static int		cmp(void *a, void *b)
{
	return ((t_zone*)a)->blocks > ((t_zone*)b)->blocks;
}

static void		sortp(void **a, int n, int (*cmp)(void *a, void *b))
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (cmp(a[j], a[j + 1]))
			{
				void *tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}

void			show_alloc_mem(void)
{
	t_zone *sorted[ZONE_NUM];
	for (int i = 0; i < ZONE_NUM; i++)
		sorted[i] = &g_zones[i];
	sortp((void**)sorted, ZONE_NUM, cmp);

	size_t bytes = 0;
	for (int i = 0; i < ZONE_NUM; i++)
	{
		if (sorted[i]->blocks != NULL)
		{
			print_head(sorted[i]);
			bytes += print_zone(sorted[i]);
		}
	}

	if (bytes > 0)
	{
		ft_putstr("Total");
		ft_putstr(" : ");
		ft_putnbr(bytes);
		ft_putstr(" bytes\n");
	}
}

