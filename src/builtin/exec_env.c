#include "minishell.h"

int	exec_env(char **com, t_env **env)
{
	// size_t	cnt;
	t_env	*top;

	(void)com;
	// cnt = 0;
	top = *env;
	while (top)
	{
		ft_putstr_fd(top->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(top->value, 1);
		top = top->next;
	}
	return (SUCCESS);
}
