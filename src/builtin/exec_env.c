#include "minishell.h"

int	exec_env(void)
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env)
		ft_putendl_fd(*env++, 1);
	return (SUCCESS);
}
