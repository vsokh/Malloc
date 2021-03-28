#include "../inc/malloc.h"

/* A simple one 4KB allocation and deallocation */
# define K 1024
int main()
{
	void *p = malloc(4 * K);
 	if (p == NULL)
		return 1;
	free(p);
#ifdef M
	show_alloc_mem();
#endif

	return 0;
}

