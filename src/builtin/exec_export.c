#include "minishell.h"

int	exec_export(char **com, t_env **env)
{
	// size_t		cnt;
	size_t		len;
	t_env		*pre;
	t_env		*tmp;
	t_env		*top;
	char		*key;

	// cnt = 0;
	len = 0;
	if (com[1] == NULL)
	{
		top = *env;
		while (top)
		{
			len += 1;
			top = top->next;
		}
		pre = (t_env *)alloc_exit(sizeof(t_env) ,1);
		pre->key = (char *)alloc_exit(sizeof(char) ,2);
		pre->key[0] = 1;
		pre->key[1] = '\0';
		while (len--)
		{
			// cnt = 0;
			tmp = (t_env *)alloc_exit(sizeof(t_env) ,1);
			tmp->key = (char *)alloc_exit(sizeof(char) ,2);
			tmp->key[0] = 127;
			tmp->key[1] = '\0';
			top = *env;
			while (top)
			{
				if (ft_strncmp(pre->key, top->key, ft_strlen(top->key)) < 0 && ft_strncmp(tmp->key, top->key, ft_strlen(top->key)) >= 0)
					tmp = top;
				top = top->next;
			}
			pre = tmp;
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(pre->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(pre->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
	}
	else
	{
		key = ft_substr(com[1], 0, ft_strlen(com[1]) - ft_strlen(ft_strchr(com[1], '=')));
		top = *env;
		while (top)
		{
			if (ft_strncmp(top->key, key, ft_strlen(key)) == 0)
				break ;
			top = top->next;
		}
		if (top)
			top->value = ft_substr(com[1], ft_strlen(key) + 1, ft_strlen(com[1]) - ft_strlen(key) - 1);
		else
		{
			tmp = (t_env *)alloc_exit(sizeof(t_env), 1);
			tmp->key = key;
			tmp->value = ft_substr(com[1], ft_strlen(key) + 1, ft_strlen(com[1]) - ft_strlen(tmp->key) - 1);
			tmp->prev = top;
			tmp->next = NULL;
			top->next = tmp;
		}
	}
	return (SUCCESS);
}
