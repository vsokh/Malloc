#include "../inc/malloc.h"

/* A simple loop call test for tiny zone. */

int main()
{
	int i = 0;
	while (i < 5)
	{
		if (malloc(1) == NULL)
			return 1;
		i++;
	}
#ifdef M
	show_alloc_mem();
#endif

	return 0;
}
