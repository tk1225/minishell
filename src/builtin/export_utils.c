#include "minishell.h"

int	put_env(t_env *env)
{
	if (ft_putstr_fd("declare -x ", 1) == -1)
		return (-1);
	if (ft_putstr_fd(env->key, 1) == -1)
		return (-1);
	if (ft_strlen(env->value) != 0)
	{
		if (ft_putstr_fd("=\"", 1) == -1)
			return (-1);
		if (ft_putstr_fd(env->value, 1) == -1)
			return (-1);
		if (ft_putstr_fd("\"", 1) == -1)
			return (-1);
	}
	if (ft_putstr_fd("\n", 1) == -1)
		return (-1);
	return (0);
}

t_env	*make_env(char c)
{
	t_env		*tmp;

	tmp = (t_env *)alloc_exit(sizeof(t_env), 1);
	tmp->key = (char *)alloc_exit(sizeof(char), 2);
	tmp->key[0] = c;
	tmp->key[1] = '\0';
	return (tmp);
}

void	add_back_env(t_env *env, char *key, char *value)
{
	t_env		*tmp;

	tmp = (t_env *)alloc_exit(sizeof(t_env), 1);
	tmp->key = key;
	tmp->value = value;
	tmp->prev = env;
	tmp->next = NULL;
	env->next = tmp;
}

void	bubble_sort(char **arr)
{
	size_t	cnt1;
	size_t	cnt2;
	char	*tmp;

	cnt1 = 0;
	while (arr[cnt1])
	{
		cnt2 = cnt1 + 1;
		while (arr[cnt2])
		{
			if (ft_strncmp(arr[cnt1], arr[cnt2], ft_strlen(arr[cnt1])) > 0)
			{
				tmp = arr[cnt1];
				arr[cnt1] = arr[cnt2];
				arr[cnt2] = tmp;
			}
			cnt2 += 1;
		}
		cnt1 += 1;
	}
}
