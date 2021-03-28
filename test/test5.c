#include "../inc/malloc.h"

/* A simple one 4KB allocation */
# define K 1024
int main()
{
	if (malloc(4 * K) == NULL)
		return 1;
#ifdef M
	show_alloc_mem();
#endif

	return 0;
}

