#include "minishell.h"

int	exec_pwd(char **com, t_env **env)
{
	char	path[512];

	(void)com;
	(void)env;
	getcwd(path, sizeof(path));
	ft_putendl_fd(path, 1);
	return (SUCCESS);
}
