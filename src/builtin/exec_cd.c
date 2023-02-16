#include "minishell.h"

int	exec_cd(char **com, char **envp)
{
	size_t	row;
	char	*path;
	char	*pwd;

	(void)envp;
	row = 1;
	path = NULL;
	if (!com[row])
	{
		pwd = getcwd(NULL, 0);
		path = getenv("HOME");
		chdir(path);
	}
	return (SUCCESS);
}
