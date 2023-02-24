#include "minishell.h"

int	exec_set(char **com, t_env **env)
{
	size_t	com_len;

	com_len = ft_strlen(com[0]) + 1;
	if (ft_strncmp(com[0], "cd", com_len) == 0)
		return (exec_cd(com, env));
	else if (ft_strncmp(com[0], "echo", com_len) == 0)
		return (exec_echo(com, env));
	else if (ft_strncmp(com[0], "env", com_len) == 0)
		return (exec_env(com, env));
	else if (ft_strncmp(com[0], "exit", com_len) == 0)
		return (exec_exit(com, env));
	else if (ft_strncmp(com[0], "export", com_len) == 0)
		return (exec_export(com, env));
	else if (ft_strncmp(com[0], "pwd", com_len) == 0)
		return (exec_pwd(com, env));
	else if (ft_strncmp(com[0], "unset", com_len) == 0)
		return (exec_unset(com, env));
	return (FAILURE);
}
