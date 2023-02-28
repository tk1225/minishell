#include "minishell.h"

int	exec_env(char **com, t_env **env)
{
	t_env	*top;

	(void)com;
	top = *env;
	while (top)
	{
		if (ft_strlen(top->key) && ft_strlen(top->value))
		{
			if (ft_putstr_fd(top->key, 1) == -1)
				return (FAILURE);
			if (ft_putchar_fd('=', 1) == -1)
				return (FAILURE);
			if (ft_putendl_fd(top->value, 1) == -1)
				return (FAILURE);
		}
		top = top->next;
	}
	return (SUCCESS);
}
