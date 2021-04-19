#include "../inc/malloc.h"

/* A simple one KB allocation for small zone */
# define K 1024-sizeof(t_meta_data)

int main()
{
	if (malloc(K) == NULL)
		return 1;
#ifdef DEBUG
	show_alloc_mem();
#endif

	return 0;
}
