#include "../inc/malloc.h"

/* A simple one call test for tiny zone and then free */
int main()
{
	void *p = malloc(1);
	if (p == NULL)
		return 1;
	free(p);
#ifdef M
	show_alloc_mem();
#endif

	return 0;
}
