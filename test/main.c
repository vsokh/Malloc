#include "../inc/malloc.h"

int main(void)
{
	void *p = malloc(1);
	show_mem();
	return 0;
}
