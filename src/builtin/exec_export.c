#include "minishell.h"

int	exec_export(char **com, char **envp)
{
	size_t		cnt;

	if (com[1] == NULL)
	{
		exec_env(com, envp);
		return (SUCCESS);
	}
	cnt = 0;
	while (envp[cnt])
		cnt += 1;
	envp[cnt++] = com[1];
	envp[cnt] = NULL;
	return (SUCCESS);
}
