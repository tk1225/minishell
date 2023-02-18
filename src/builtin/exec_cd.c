#include "minishell.h"

int	exec_cd(char **com, char **envp)
{
	size_t	row;
	size_t	cnt;
	char	*path;
	char	*pwd;

	(void)envp;
	pwd = getcwd(NULL, 512);
	row = 1;
	if (!com[row] || ft_strncmp(com[row], "~" ,1) == 0)
	{
		path = getenv("HOME");
		chdir(path);
	}
	else if (ft_strncmp(com[row], ".." ,2) == 0)
	{
		cnt = ft_strlen(ft_strrchr(pwd, '/'));
		path = ft_substr(pwd, 0, ft_strlen(pwd) - cnt);
		chdir(path);
	}
	else if (ft_strncmp(com[row], "/" ,1) == 0)
	{
		chdir(com[row]);
	}
	else if (ft_strncmp(com[row], "./" ,2) == 0)
	{
		path = ft_strjoin(pwd, &com[row][1]);
		chdir(path);
	}
	else if (ft_strncmp(com[row], "." ,2) == 0)
	{
		chdir(path);
	}
	else if (ft_strncmp(com[row], "-" ,1) == 0)
	{
		path = getenv("OLDPWD");
		chdir(path);
	}
	else
	{
		path = str_join_three(pwd, "/", com[row]);
		chdir(path);
	}
	return (SUCCESS);
}
