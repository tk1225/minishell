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
			ft_putstr_fd(top->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(top->value, STDOUT_FILENO);
		}
		top = top->next;
	}
	return (SUCCESS);
}
