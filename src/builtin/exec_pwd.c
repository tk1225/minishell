#include "minishell.h"

int	exec_pwd(char **com, char **envp)
{
	char	*path_pwd;

	(void)com;
	(void)envp;
	path_pwd = getenv("PWD");
	ft_putendl_fd(path_pwd, 1);
	return (SUCCESS);
}
