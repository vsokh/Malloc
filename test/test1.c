#include "../inc/malloc.h"

/* A simple one call test for tiny zone. */
int main()
{
	if (malloc(1) == NULL)
	{
		show_alloc_mem();
		return 1;
	}
#ifdef M
	show_alloc_mem();
#endif

	return 0;
}
