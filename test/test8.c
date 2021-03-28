
#include "../inc/malloc.h"

/* A simple loop of malloc & free calls for tiny zone. */

int main()
{
	int i = 0;
	while (i < 5)
	{
		void *p = malloc(1);
		if (p == NULL)
			return 1;
		free(p);
		i++;
	}
#ifdef M
	show_alloc_mem();
#endif

	return 0;
}
