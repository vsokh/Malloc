#include "../inc/malloc.h"

/* Double free for small zone */

# define K 1024
int main()
{
	void *p = malloc(K/2);
	free(p);
	free(p);
	return 0;
}

