#include "minishell.h"
// #include "exec.h"

int	exec_pwd(void)
{
	char *path_pwd;

	path_pwd = getenv("PWD");
	ft_putendl_fd(path_pwd, 1);
	return (1);
}