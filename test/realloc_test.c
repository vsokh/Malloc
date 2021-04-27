#include "../inc/malloc.h"

int bad_inputs_realloc(void)
{
	if (realloc(NULL, 1))
	{
		ft_putstr("realloc(NULL, 1) should return NULL\n");
		return 1;
	}
	if (realloc(NULL, 0))
	{
		ft_putstr("realloc(NULL, 0) should return NULL\n");
		return 1;
	}
	if (realloc(malloc(1), 0))
	{
		ft_putstr("realloc(malloc(1), 0) should return NULL\n");
		return 1;
	}
	return 0;
}

int strneq(char const *s1, char const *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL || n == 0)
		return 0;

	char *cs1 = (char*)s1;
	char *cs2 = (char*)s2;
	while (cs1 && cs2 && n)
	{
		if (*cs1 != *cs2)
			return 0;
		cs1++;
		cs2++;
		n--;
	}
	return 1;
}

int realloc_test(char const *s, size_t n)
{
	char *p1 = malloc(n);
	ft_strcpy(p1, s);

	char *p2 = realloc(p1, n);
	return strneq(p1, p2, n);
}

struct s_test
{
	char* str;
	int size;
	int ret;
};

void *realloc_cb(void *ptr)
{
	if (ptr == NULL)
		return NULL;

	struct s_test *test = (struct s_test*)ptr;
	test->ret = realloc_test(test->str, test->size);
	return NULL;
}

int main(void)
{
	if (bad_inputs_realloc())
		return 1;

	char const *str = "HELLO";
	int  const tests_num = 128;

	pthread_t threads[tests_num];
	struct s_test tests[tests_num];
	for (int test_idx = 1; test_idx < tests_num; test_idx++)
	{
		tests[test_idx] = (struct s_test){
			.str = (char*)str, .size = test_idx, .ret = 0
		};
		pthread_create(&threads[test_idx], NULL, realloc_cb, &tests[test_idx]);
	}
	for (int test_idx = 1; test_idx < tests_num; test_idx++)
	{
		pthread_join(threads[test_idx], NULL);
	}
	for (int test_idx = 1; test_idx < tests_num; test_idx++)
	{
		if (!tests[test_idx].ret)
			return 1;
	}
	return 0;
}

