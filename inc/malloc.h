/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:27:30 by vsokolog          #+#    #+#             */
/*   Updated: 2021/10/09 19:22:10 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>

# include <pthread.h>

# include <unistd.h>

# include <stdint.h>

# include <stdio.h>

# define MIN_SIZE				(2 * sizeof(size_t))
# define PAGE_SIZE 				((size_t)getpagesize())

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

# define minsize(x)					\
	((x < MIN_SIZE) ? MIN_SIZE : x)

# define req2size(x)				\
	(minsize(x) + BLOCK_METADATA_SIZE)

# define head_at(zone, idx)			\
	((zone->blocks) ? ((void*)((char*)(zone)->blocks) + ((zone)->block_size * idx)) : NULL)

# define block2mem(block)			\
	((block) ? ((void*)((char*)(block) + BLOCK_METADATA_SIZE)) : NULL)

# define mem2block(mem)				\
	((mem) ? ((void*)((char*)(mem) - BLOCK_METADATA_SIZE)) : NULL)

# define datasize(block)			\
	((block) ? ((block)->size - BLOCK_METADATA_SIZE) : 0)

# define IS_INUSE 0x1
# define IS_FIRST 0x2
# define IS_LAST 0x4

# define is_inuse(block)			\
	((block) ? (block->flags & IS_INUSE) : 0)

# define is_first(block)			\
	((block) ? (block->flags & IS_FIRST) : 0)

# define is_last(block)				\
	((block) ? (block->flags & IS_LAST) : 0)

typedef enum
{
	TINY = 0, SMALL, LARGE
}						e_zone_type;

typedef struct			s_meta_data
{
	struct s_meta_data	*prev;
	struct s_meta_data	*next;

	size_t				flags;
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

extern t_zone			g_zones[];
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


void					ft_putnbr(size_t n);
void					ft_putnbr16(unsigned long long n);

void					ft_putstr(char const *s);
int						ft_strlen(char const *s);
void					ft_strcpy(char *dest, char const *src);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					ft_bzero(void *p, size_t size);

#endif
