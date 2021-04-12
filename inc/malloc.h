
#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>

# include <unistd.h>

# include <sys/mman.h>

# include <sys/resource.h>

# include <string.h>

# include <errno.h>

/* # define TINY_PAGES		(1 << 2) /1*  4 pages *1/ */
/* # define SMALL_PAGES		(1 << 5) /1* 32 pages *1/ */

# define MIN_SIZE			(2 * sizeof(size_t))
# define PAGE_SIZE 			(getpagesize())

# define AVAIL 				0x1
# define PARTIAL			0x2
# define FULL 				0x4

# define TINY_SLAB_SIZE		(1 << 7)  /*  128 bytes  */
# define SMALL_SLAB_SIZE	(1 << 10) /* 1024 bytes  */
# define SLABS				(1 << 7)  /*  128        */

# define TINY_ZONE_SIZE		(SLABS * TINY_SLAB_SIZE)
# define SMALL_ZONE_SIZE	(SLABS * SMALL_SLAB_SIZE)

# define align(x, alignment)	\
	(((x) + (alignment) - 1) & ~((alignment) - 1))

# define align2page(x)			\
	(align(x, PAGE_SIZE))

# define align2minsize(x)		\
	(align(x, MIN_SIZE))

# define size2blocksz(x)		\
	(align2minsize(x) + sizeof(struct s_block))

# define block2mem(block)		\
	((void*)((char*)block + sizeof(struct s_block)))

# define mem2block(mem)			\
	((void*)((char*)mem - sizeof(struct s_block)))

# define datasize(block)		\
	(((block)->size) - sizeof(struct s_block))

# define isinuse(block)			\
	((block)->inuse & AVAIL)

typedef struct		s_block
{
	struct s_block	*prev;
	struct s_block	*next;
	size_t			inuse;
	size_t			size;
}					t_block;

typedef struct		s_slab
{
	struct s_block	*blocks;
	/* size_t			flags; /1* Avail, partial, full *1/ */
}					t_slab;

typedef struct		s_arena
{
	struct s_slab	tiny_zone[SLABS];
	struct s_slab	small_zone[SLABS];
	struct s_block	*large_zone;
}					t_arena;

extern t_arena		g_arena;
void				*malloc(size_t size);
void				free(void *ptr);

void				show_alloc_mem(void);

#endif
