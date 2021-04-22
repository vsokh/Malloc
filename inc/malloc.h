/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:27:30 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/22 15:48:42 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>

# include <errno.h>

# include <pthread.h>

# include <unistd.h>

# define MIN_SIZE				(2 * sizeof(size_t))
# define PAGE_SIZE 				(getpagesize())

# define TINY_DATA_SIZE			128
# define SMALL_DATA_SIZE		1024
# define ALLOCATIONS			128
# define ZONE_NUM  				3

# define BLOCK_METADATA_SIZE	sizeof(t_meta_data)

# define TINY_ZONE_SIZE			(TINY_DATA_SIZE  * ALLOCATIONS)
# define SMALL_ZONE_SIZE		(SMALL_DATA_SIZE * ALLOCATIONS)

# define TINY_BLOCK_SIZE		(BLOCK_METADATA_SIZE + TINY_DATA_SIZE)
# define SMALL_BLOCK_SIZE		(BLOCK_METADATA_SIZE + SMALL_DATA_SIZE)

# define TINY_HEADS_NUM			(TINY_ZONE_SIZE  / TINY_BLOCK_SIZE)
# define SMALL_HEADS_NUM		(SMALL_ZONE_SIZE / SMALL_BLOCK_SIZE)
# define LARGE_HEADS_NUM		1

# define _align(x, alignment)		\
	(((x) + (alignment) - 1) & ~((alignment) - 1))

# define align2page(x)				\
	((x) ? (_align(x, PAGE_SIZE)) : PAGE_SIZE)

# define align2minsize(x)			\
	((x) ? (_align(x, MIN_SIZE)) : MIN_SIZE)

# define req2size(x)				\
	(align2minsize(x) + BLOCK_METADATA_SIZE)

# define head_at(zone, idx)			\
	((zone->blocks) ? ((void*)((char*)(zone)->blocks + (zone)->block_size * idx)) : NULL)

# define block2mem(block)			\
	((block) ? ((void*)((char*)(block) + BLOCK_METADATA_SIZE)) : NULL)

# define mem2block(mem)				\
	((mem) ? ((void*)((char*)(mem) - BLOCK_METADATA_SIZE)) : NULL)

# define datasize(block)			\
	((block) ? ((block)->size - BLOCK_METADATA_SIZE) : 0)

typedef enum
{
	TINY = 0, SMALL, LARGE
}						e_zone_type;

typedef struct			s_meta_data
{
	struct s_meta_data	*prev;
	struct s_meta_data	*next;

	size_t				inuse;
	size_t				size;
}						t_meta_data;

typedef struct			s_zone
{
	t_meta_data			*blocks;
	char				*name;
	size_t				block_size;
	size_t				heads_num;
	size_t				free_space;
}						t_zone;

extern t_zone			g_zones[ZONE_NUM];
extern pthread_mutex_t	g_mtx;

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

void					*alloc_mem(size_t size);

void					*try_alloc_tinysmall_block(size_t size);
int						try_free_tinysmall_block(void *ptr);

void					*try_alloc_large_block(size_t size);
void					try_free_large_block(void *ptr);

void					show_alloc_mem(void);
void					print_block(t_meta_data *block);

#endif
