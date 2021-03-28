#include "../inc/malloc.h"

/* Double free for large zone */

# define K 1024
int main()
{
	void *p = malloc(K*K);
	free(p);
	free(p);
	return 0;
}

