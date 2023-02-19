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
		if (ft_strlen(com[1]) > 2 && com[1][2] == '/')
			path = ft_strjoin(path, ft_substr(com[row], 2, ft_strlen(com[row]) - 2));
		if (access(com[row], F_OK) == 0)
			chdir(com[row]);
		else
		{
			perror("path error");
			return (FAILURE);
		}
	}
	else if (ft_strncmp(com[row], "/" ,1) == 0)
	{
		if (access(com[row], F_OK) == 0)
			chdir(com[row]);
		else
		{
			perror("path error");
			return (FAILURE);
		}
	}
	else if (ft_strncmp(com[row], "./" ,2) == 0)
	{
		path = ft_strjoin(pwd, &com[row][1]);
		if (access(com[row], F_OK) == 0)
			chdir(com[row]);
		else
		{
			perror("path error");
			return (FAILURE);
		}
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
		if (access(com[row], F_OK) == 0)
			chdir(com[row]);
		else
		{
			perror("path error");
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
