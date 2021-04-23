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
	/* if (malloc(LONG_MAX)) */
	/* { */
	/* 	ft_putstr("malloc(LONG_MAX) should return NULL\n"); */
	/* 	return 1; */
	/* } */
	/* if (malloc(LLONG_MAX)) */
	/* { */
	/* 	ft_putstr("malloc(LLONG_MAX) should return NULL\n"); */
	/* 	return 1; */
	/* } */
	return 0;
}

void *tiny_cb(void *ptr)
{
	(void)ptr;
	malloc(1);
	return NULL;
}

void *small_cb(void *ptr)
{
	(void)ptr;
	malloc(TINY_DATA_SIZE+1);
	return NULL;
}

int main(void)
{
	malloc_tiny();
	malloc_small();
	malloc_large();

	if (bad_inputs_malloc())
		return 1;

	/* size_t max_tiny_allocs = 3*TINY_HEADS_NUM; */
	/* for (size_t i=0; i< max_tiny_allocs; i++) { */
	/* 	malloc(1); */
	/* } */
	/* pthread_t t[max_tiny_allocs]; */
	/* int iret[max_tiny_allocs]; */
	/* for (size_t i=0; i< max_tiny_allocs; i++) { */
	/* 	pthread_create(&t[i], NULL, tiny_cb, NULL); */
	/* } */
	/* for (size_t i=0; i< max_tiny_allocs; i++) { */
	/* 	pthread_join(t[i], NULL); */
	/* } */
	/* for (size_t i=0; i< max_tiny_allocs; i++) { */
	/* 	printf("Thread %zu ret: %d\n", i, iret[i]); */
	/* } */

	/* size_t max_small_allocs = 6*SMALL_HEADS_NUM; */
	/* for (size_t i=0; i< max_small_allocs; i++) { */
	/* 	malloc(TINY_DATA_SIZE+1); */
	/* } */

	/* pthread_t t[max_small_allocs]; */
	/* int iret[max_small_allocs]; */
	/* for (size_t i=0; i< max_small_allocs; i++) { */
	/* 	pthread_create(&t[i], NULL, small_cb, NULL); */
	/* } */
	/* for (size_t i=0; i< max_small_allocs; i++) { */
	/* 	pthread_join(t[i], NULL); */
	/* } */
	/* for (size_t i=0; i< max_small_allocs; i++) { */
	/* 	printf("Thread %zu ret: %d\n", i, iret[i]); */
	/* } */
	show_alloc_mem();

	return 0;
}

