#include "../inc/malloc.h"

/* A simple one KB allocation and deallocation for small zone */
# define K 1024

int main()
{
	void *p = malloc(K);
	if (p == NULL)
		return 1;
	free(p);
#ifdef M
	show_alloc_mem();
#endif

	return 0;
}
