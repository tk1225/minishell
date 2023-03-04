#include "minishell.h"

static int	access_cd(char *path, t_env **env)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (access(path, F_OK) == 0)
	{
		if (ch_dir(path) == -1)
			return (FAILURE);
		if (!getcwd(cwd, PATH_MAX))
			return (FAILURE);
		pwd = ft_strjoin("PWD=", cwd);
		if (!pwd)
			return (FAILURE);
		if (add_env(pwd, env) == FAILURE)
			return (FAILURE);
		free(pwd);
		return (SUCCESS);
	}
	else
	{
		free(path);
		perror("path not found");
		return (FAILURE);
	}
}

static int	update_oldpwd(t_env **env)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	if (!getcwd(cwd, PATH_MAX))
		return (FAILURE);
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (!old_pwd)
		return (FAILURE);
	if (add_env(old_pwd, env) == FAILURE)
		return (FAILURE);
	free(old_pwd);
	return (SUCCESS);
}

int	exec_cd(char **com, t_env **env)
{
	char	*path;

	(void)env;
	if (!com[1] || ft_strncmp(com[1], "~", 2) == 0 || \
		ft_strncmp(com[1], "--", 3) == 0)
		path = get_env("HOME", env);
	else if (ft_strncmp(com[1], "-", 2) == 0)
		path = get_env("OLDPWD", env);
	else
		path = ft_strdup(com[1]);
	if (update_oldpwd(env) == FAILURE)
		return (FAILURE);
	return (access_cd(path, env));
}
