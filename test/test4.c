#include "../inc/malloc.h"

/* An allocation for 2^20 bytes */
# define K (int)(1024-sizeof(t_meta_data))
int main()
{
	int i = 0;
	while (i < K)
	{
		if (malloc(K) == NULL)
		{
			show_alloc_mem();
			return 1;
		}
		i++;
	}
#ifdef DEBUG
	show_alloc_mem();
#endif

	return 0;
}
