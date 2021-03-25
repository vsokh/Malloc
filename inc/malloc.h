/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:55:41 by vsokolog          #+#    #+#             */
/*   Updated: 2021/03/25 15:48:26 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <string.h>

typedef struct		s_block
{
	struct s_block	*prev;
	struct s_block	*next;
	uint8_t			inuse;
	size_t			size;
}					t_block;

extern t_block		*g_first;
extern t_block		*g_last;

void				*malloc(size_t size);
void				free(void* ptr);

size_t				align4(size_t x);
size_t				align_to_page(size_t x);
void				show_mem(void);

#endif
