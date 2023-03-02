#include "minishell.h"

int	exec_pwd(char **com, t_env **env)
{
	char	cwd[PATH_MAX];

	(void)com;
	(void)env;
	if (!getcwd(cwd, PATH_MAX))
		return (FAILURE);
	if (ft_putendl_fd(cwd, 1) == -1)
		return (FAILURE);
	return (SUCCESS);
}
