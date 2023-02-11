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

char	*str_join_three(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	size_t	t_cnt;
	size_t	s_cnt;

	if (!s1 && !s2 && !s3)
		return (NULL);
	if (!s1)
		return (ft_strjoin(s2, s3));
	if (!s2)
		return (ft_strjoin(s1, s3));
	if (!s3)
		return (ft_strjoin(s1, s2));
	tmp = (char *)alloc_exit(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	s_cnt = 0;
	t_cnt = 0;
	while (s1[s_cnt])
		tmp[t_cnt++] = s1[s_cnt++];
	s_cnt = 0;
	while (s2[s_cnt])
		tmp[t_cnt++] = s2[s_cnt++];
	s_cnt = 0;
	while (s3[s_cnt])
		tmp[t_cnt++] = s3[s_cnt++];
	tmp[t_cnt] = '\0';
	return (tmp);
}
