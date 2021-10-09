#include "../inc/malloc.h"
#include <pthread.h>

void free_test(int s, int n)
{
	free(NULL);

	void *pp = malloc(s);
	free(pp - 500);
	free(pp);
	free(pp);

	void *p[n];

	/* forward free */
	for (int i = 0; i < n; i++)
		p[i] = malloc(s);
	for (int i = 0; i < n; i++)
		free(p[i]);

	/* backward free */
	for (int i = 0; i < n; i++)
		p[i] = malloc(s);
	for (int i = n-1; i >= 0; i--)
		free(p[i]);
}

void *tiny_cb(void *ptr)
{
	ft_putstr("TINY\n");
	(void)ptr;
	free_test(1, TINY_HEADS_NUM);
	return NULL;
}

void *small_cb(void *ptr)
{
	ft_putstr("SMALL\n");
	(void)ptr;
	free_test(TINY_DATA_SIZE+1, SMALL_HEADS_NUM);
	return NULL;
}

#define K 1024
void *large_cb(void *ptr)
{
	ft_putstr("LARGE\n");
	(void)ptr;
	free_test(SMALL_DATA_SIZE+1, K);
	return NULL;
}

int main(void)
{
	free_test(1, TINY_HEADS_NUM);
	free_test(TINY_DATA_SIZE+1, SMALL_HEADS_NUM);
	/* free_test(SMALL_DATA_SIZE+1, K); */

/* 	pthread_t t[ZONE_NUM]; */
/* 	pthread_create(&t[TINY], NULL, tiny_cb, NULL); */
/* 	pthread_create(&t[SMALL], NULL, small_cb, NULL); */
/* 	pthread_create(&t[LARGE], NULL, large_cb, NULL); */

/* 	pthread_join(t[TINY], NULL); */
/* 	pthread_join(t[SMALL], NULL); */
/* 	pthread_join(t[LARGE], NULL); */

	return 0;
}
