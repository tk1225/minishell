#include "minishell.h"

int	exec_env(char **com, char **envp)
{
	size_t	cnt;

	(void)com;
	cnt = 0;
	while (envp[cnt])
		ft_putendl_fd(envp[cnt++], 1);
	return (SUCCESS);
}
