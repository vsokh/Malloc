#include "../inc/malloc.h"

/* An allocation for 2^20 bytes */
# define K 1024
int main()
{
	int i = 0;
	while (i < K)
	{
		if (malloc(K) == NULL)
			return 1;
		i++;
	}
#ifdef M
	show_alloc_mem();
#endif

	return 0;
}
