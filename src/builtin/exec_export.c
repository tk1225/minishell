#include "minishell.h"

int	exec_export(char **com)
{
	extern char	**environ;
	char		**env;
	size_t		cnt;

	if (com[1] == NULL)
	{
		exec_env();
		return (SUCCESS);
	}
	env = environ;
	cnt = 0;
	while (env[cnt])
		cnt += 1;
	env[cnt++] = com[1];
	env[cnt] = NULL;
	return (SUCCESS);
}
