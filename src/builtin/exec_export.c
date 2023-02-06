#include "minishell.h"

int	exec_export(char **com)
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env)
		env++;
	*env++ = com[1];
	*env = NULL;
	return (SUCCESS);
}
