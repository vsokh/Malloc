#include "../inc/malloc.h"

/* A simple one call test for tiny zone. */
int main()
{
	void *l = malloc(4096);
	void *s = malloc(1024);
	void *t = malloc(1);
	(void)l;
	(void)s;
	(void)t;
	/* free(l); */
	/* free(s); */
	/* free(t); */
	show_alloc_mem();
	return 0;
}
