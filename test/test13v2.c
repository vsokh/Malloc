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
	while (--i >= 0)
		free(p[i]);
#ifdef M
	show_alloc_mem();
#endif
	return 0;
}
