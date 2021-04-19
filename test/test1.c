#include "../inc/malloc.h"

/* A simple one call test for tiny zone. */
int main()
{
	void *p[5];
	int i = 0;
	while (i < 5) {
		p[i] = malloc(1);
		if (p[i] == NULL) {
			return 1;
		}
		i++;
	}
#ifdef DEBUG
	show_alloc_mem();
#endif
	i = 0;
	while (i < 5) {
		free(p[i]);
		i++;
	}
	return 0;
}
