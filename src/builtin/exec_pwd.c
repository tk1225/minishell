#include "minishell.h"

int	exec_pwd(char **com, char **envp)
{
	char	path[512];

	(void)com;
	(void)envp;
	getcwd(path, sizeof(path));
	ft_putendl_fd(path, 1);
	return (SUCCESS);
}
