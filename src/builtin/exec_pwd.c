#include "minishell.h"

int	exec_pwd(char **com, t_env **env)
{
	char	cwd[PATH_MAX];

	(void)com;
	(void)env;
	if (!getcwd(cwd, PATH_MAX))
		return (FAILURE);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (SUCCESS);
}
