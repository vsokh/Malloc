#include "../inc/malloc.h"

# define K 1024

int main()
{
	int i = 0;
	const int t = 5;
	void *p[K*t];
	while (i < K*t)
	{
		p[i] = malloc(5);
		if (p[i] == NULL)
			return 1;
		i++;
	}
	i = 0;
	while (i < K*t)
	{
		free(p[i]);
		i++;
		//printf("K*t: %d i: %d\n", K*t,i);
	}
#ifdef M
	show_alloc_mem();
#endif
	return 0;
}
