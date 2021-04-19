#include "../inc/malloc.h"

# define K 1024

int main()
{
	int i = 0;
	const int k = 5;
	while (i < K*k)
	{
		if (malloc(5) == NULL)
			return 1;
		i++;
	}
#ifdef DEBUG
	show_alloc_mem();
#endif
	return 0;
}
