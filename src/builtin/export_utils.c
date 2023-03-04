#include "minishell.h"

int	put_env(t_env *env)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->key, STDOUT_FILENO);
	if (ft_strlen(env->value) != 0)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO) ;
		ft_putstr_fd(env->value, STDOUT_FILENO) ;
		ft_putstr_fd("\"", STDOUT_FILENO) ;
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
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

int	add_back_env(t_env **env, char *key, char *value)
{
	t_env		*tmp;

	tmp = (t_env *)alloc_exit(sizeof(t_env), 1);
	if (!tmp)
		return (FAILURE);
	tmp->key = key;
	tmp->value = value;
	tmp->prev = *env;
	tmp->next = NULL;
	(*env)->next = tmp;
	return (SUCCESS);
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

int	invalid_identifier(char *key)
{
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	free(key);
	return (FAILURE);
}
