#include "../inc/malloc.h"

/* A simple one KB allocation for small zone */
# define K 1024

int main()
{
	if (malloc(K) == NULL)
		return 1;
#ifdef M
	show_alloc_mem();
#endif

	return 0;
}
