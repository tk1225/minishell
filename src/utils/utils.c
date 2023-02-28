#include "minishell.h"

void	*alloc_exit(size_t cnt, size_t size)
{
	void	*tmp;

	tmp = NULL;
	if (cnt == 0 || size == 0)
		tmp = (void *)malloc(sizeof(void) * 1);
	else if (cnt > INT_MAX / size)
		perror("malloc error");
	else
		tmp = (void *)malloc(sizeof(void) * size * cnt);
	if (!tmp)
		perror("malloc error");
	return (tmp);
}

char	*join_three(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	size_t	cnt;
	size_t	len;

	if (!s1 && !s2 && !s3)
		return (NULL);
	if (!s1)
		return (ft_strjoin(s2, s3));
	if (!s2)
		return (ft_strjoin(s1, s3));
	if (!s3)
		return (ft_strjoin(s1, s2));
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	tmp = (char *)alloc_exit(sizeof(char), len + 1);
	cnt = 0;
	while (*s1)
		tmp[cnt++] = *s1++;
	while (*s2)
		tmp[cnt++] = *s2++;
	while (*s3)
		tmp[cnt++] = *s3++;
	tmp[cnt] = '\0';
	return (tmp);
}