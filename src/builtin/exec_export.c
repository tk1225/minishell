#include "minishell.h"

void	put_env(t_env *env)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	if (ft_strlen(env->value) != 0)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
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

int	sort_env(t_env **env)
{
	size_t	len;
	t_env	*pre;
	t_env	*tmp;
	t_env	*top;

	len = 0;
	top = *env;
	while (top)
	{
		len += 1;
		top = top->next;
	}
	pre = make_env(1);
	while (len--)
	{
		tmp = make_env(127);
		top = *env;
		while (top)
		{
			if (ft_strncmp(pre->key, top->key, ft_strlen(top->key) + 1) < 0 && ft_strncmp(tmp->key, top->key, ft_strlen(top->key) + 1) >= 0)
				tmp = top;
			top = top->next;
		}
		pre = tmp;
		put_env(pre);
	}
	return (SUCCESS);
}

int	add_env(char *com, t_env **env)
{
	t_env		*tmp;
	t_env		*top;
	char		*key;

	key = ft_substr(com, 0, ft_strlen(com) - ft_strlen(ft_strchr(com, '=')));
	top = *env;
	while (top)
	{
		if (ft_strncmp(top->key, key, ft_strlen(key) + 1) == 0)
		{
			top->value = ft_substr(com, ft_strlen(key) + 1, ft_strlen(com) - ft_strlen(key) - 1);
			return (SUCCESS);
		}
		if (!top->next)
			break ;
		top = top->next;
	}
	tmp = (t_env *)alloc_exit(sizeof(t_env), 1);
	tmp->key = key;
	tmp->value = ft_substr(com, ft_strlen(key) + 1, ft_strlen(com) - ft_strlen(tmp->key) - 1);
	tmp->prev = top;
	tmp->next = NULL;
	top->next = tmp;
	return (SUCCESS);
}

int	exec_export(char **com, t_env **env)
{
	size_t	cnt;

	if (com[1] == NULL)
		return (sort_env(env));
	else
	{
		cnt = 1;
		while (com[cnt])
		{
			if (add_env(com[cnt++], env) == FAILURE)
				return (FAILURE);
		}
		return (SUCCESS);
	}
	return (FAILURE);
}
