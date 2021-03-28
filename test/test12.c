#include "../inc/malloc.h"

# define K 1024

int main()
{
	int i = 0;
	while (i < K*20)
	{
		void *p = malloc(5);
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
