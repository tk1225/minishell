#include "minishell.h"

int access_cd(char *com, t_env **env)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (access(com, F_OK) == 0)
	{
		chdir(com);
		if (!getcwd(cwd, PATH_MAX))
			return (FAILURE);
		pwd = ft_strjoin("PWD=", cwd);
		if (!pwd)
			return (FAILURE);
		add_env(pwd, env);
		free(pwd);
		return (SUCCESS);
	}
	else
	{
		perror("path error");
		return (FAILURE);
	}
}

int	update_oldpwd(t_env **env)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	if (!getcwd(cwd, PATH_MAX))
		return (FAILURE);
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (!old_pwd)
		return (FAILURE);
	add_env(old_pwd, env);
	free(old_pwd);
	return (SUCCESS);
}

int	exec_cd(char **com, t_env **env)
{
	char	*path;

	(void)env;
	if (!com[1] || ft_strncmp(com[1], "~", 2) == 0 || ft_strncmp(com[1], "--", 3) == 0)
		path = getenvs("HOME", env);
	else if (ft_strncmp(com[1], "-", 2) == 0)
		path = getenvs("OLDPWD", env);
	else
		path = strdup(com[1]);
	update_oldpwd(env);
	return (access_cd(path, env));
}
