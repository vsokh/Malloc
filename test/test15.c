#include "../inc/malloc.h"

/* Double free for tiny zone */

int main()
{
	void *p = malloc(1);
	free(p);
	free(p);
	return 0;
}
