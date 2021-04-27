#include "../inc/malloc.h"
#include <limits.h>
#include <pthread.h>

void malloc_tiny(void)
{
	char *p1 = malloc(1);
	ft_strcpy(p1, "TINY\n");
	ft_putstr(p1);

	char *p2 = malloc(TINY_DATA_SIZE);
	ft_strcpy(p2, p1);
	ft_putstr(p2);
}

void malloc_small(void)
{
	char *p1 = malloc(TINY_DATA_SIZE+1);
	ft_strcpy(p1, "SMALL\n");
	ft_putstr(p1);

	char *p2 = malloc(SMALL_DATA_SIZE);
	ft_strcpy(p2, p1);
	ft_putstr(p2);
}

void malloc_large(void)
{
	char *p1 = malloc(SMALL_DATA_SIZE+1);
	ft_strcpy(p1, "LARGE\n");
	ft_putstr(p1);

	char *p2 = malloc(INT_MAX);
	ft_strcpy(p2, p1);
	ft_putstr(p2);
}

int bad_inputs_malloc(void)
{
	if (malloc(0))
	{
		ft_putstr("malloc(0) should return NULL\n");
		return 1;
	}
	return 0;
}

int main(void)
{
	malloc_tiny();
	malloc_small();
	malloc_large();

	if (bad_inputs_malloc())
		return 1;
	show_alloc_mem();

	return 0;
}

