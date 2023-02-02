#include "minishell.h"

void	put_exit(char *str)
{
	printf("%s\n", str);
	exit(FAILURE);
}

void	*alloc_exit(size_t cnt, size_t size)
{
	void	*tmp;

	tmp = NULL;
	if (cnt == 0 || size == 0)
		tmp = (void *)malloc(sizeof(void) * 1);
	else if (cnt > INT_MAX / size)
		put_exit("malloc error");
	else
		tmp = (void *)malloc(sizeof(void) * size * cnt);
	if (!tmp)
		put_exit("malloc error");
	return (tmp);
}
