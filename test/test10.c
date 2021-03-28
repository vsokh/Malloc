#include "../inc/malloc.h"

/* An allocation and deallocation for 2^20 bytes */
# define K 1024

int main()
{
	int i = 0;
	while (i < K)
	{
		void *p = malloc(K);
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
