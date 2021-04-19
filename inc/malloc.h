/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:27:30 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/19 15:54:09 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>

# include <unistd.h>

# include <sys/mman.h>

# include <sys/resource.h>

# include <string.h>

# include <errno.h>

# include "libft.h"

# include "pthread.h"

# define MIN_SIZE				(2 * sizeof(size_t))
# define PAGE_SIZE 				(getpagesize())

# define TINY_DATA_SIZE			128
# define SMALL_DATA_SIZE		1024
# define ALLOCATIONS			128

# define BLOCK_METADATA_SIZE	sizeof(t_meta_data)
# define ZONE_METADATA_SIZE		sizeof(t_zone)

# define TINY_ZONE_SIZE			(ZONE_METADATA_SIZE + TINY_DATA_SIZE  * ALLOCATIONS)
# define SMALL_ZONE_SIZE		(ZONE_METADATA_SIZE + SMALL_DATA_SIZE * ALLOCATIONS)

# define TINY_BLOCK_SIZE		(BLOCK_METADATA_SIZE + TINY_DATA_SIZE)
# define SMALL_BLOCK_SIZE		(BLOCK_METADATA_SIZE + SMALL_DATA_SIZE)

# define TINY_BLOCKS_NUM		((TINY_ZONE_SIZE  - ZONE_METADATA_SIZE) / TINY_BLOCK_SIZE)
# define SMALL_BLOCKS_NUM		((SMALL_ZONE_SIZE - ZONE_METADATA_SIZE) / SMALL_BLOCK_SIZE)

# define align(x, alignment)		\
	(((x) + (alignment) - 1) & ~((alignment) - 1))

# define align2page(x)				\
	((x) ? (align(x, PAGE_SIZE)) : PAGE_SIZE)

# define align2minsize(x)			\
	((x) ? (align(x, MIN_SIZE)) : MIN_SIZE)

# define req2size(x)				\
	(align2minsize(x) + BLOCK_METADATA_SIZE)

# define zone2mem(zone)				\
	((zone) ? ((void*)((char*)(zone) + ZONE_METADATA_SIZE)) : NULL)

# define block_head_at(zone, idx)	\
	((zone) ? ((zone2mem(zone) + (zone)->block_size * idx)) : NULL)

# define block2mem(block)			\
	((block) ? ((void*)((char*)(block) + BLOCK_METADATA_SIZE)) : NULL)

# define mem2block(mem)				\
	((mem) ? ((void*)((char*)(mem) - BLOCK_METADATA_SIZE)) : NULL)

# define datasize(block)			\
	((block) ? ((block)->size - BLOCK_METADATA_SIZE) : 0)

typedef struct			s_meta_data
{
	struct s_meta_data	*prev;
	struct s_meta_data	*next;

	size_t				inuse;
	size_t				size;
}						t_meta_data;

typedef struct			s_zone
{
	size_t				block_size;
	size_t				block_num;
}						t_zone;

typedef struct			s_arena
{
	t_zone 				*tiny_zone;
	t_zone 				*small_zone;
	t_meta_data			*large_zone;
}						t_arena;

extern t_arena			g_arena;
extern pthread_mutex_t	g_mtx;

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

int						alloc_mem(void **mem, size_t size);

int						try_alloc_tinysmall_block(void **mem, size_t size);
int						try_free_tinysmall_block(void **ptr);

int						try_alloc_large_block(void **mem, size_t size);
int						try_free_large_block(void **ptr);

void					show_alloc_mem(void);
void					print_block(t_meta_data *block);

#endif
