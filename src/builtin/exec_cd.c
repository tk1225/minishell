#include "minishell.h"

int access_cd(char *com)
{
	if (access(com, F_OK) == 0)
	{
		chdir(com);
		free(com);
		return (SUCCESS);
	}
	else
	{
		free(com);
		perror("path error");
		return (FAILURE);
	}
}

// int	update_oldpwd(t_env **env)
// {
// 	char	pwd[PATH_MAX];
// 	char	*old_pwd;

// 	if (!getcwd(pwd, PATH_MAX))
// 		return (FAILURE);
// 	if ()
// }

int	exec_cd(char **com, t_env **env)
{
	char	*path;

	(void)env;
	if (!com[1] || ft_strncmp(com[1], "~", 1) == 0 || ft_strncmp(com[1], "--", 2) == 0)
		path = getenvs("HOME", env);
	else if (ft_strncmp(com[1], "-", 1) == 0)
		path = getenvs("OLDPWD", env);
	else
		path = strdup(com[1]);
	return (access_cd(path));
}
