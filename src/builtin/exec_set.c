#include "minishell.h"

int	exec_set(char **com)
{
	size_t	com_len;

	com_len = ft_strlen(com[0]);
	if (ft_strncmp(com[0], "cd", com_len) == 0)
		return(FAILURE);
	if (ft_strncmp(com[0], "echo", com_len) == 0)
		return(exec_echo(com));
	if (ft_strncmp(com[0], "env", com_len) == 0)
		return(exec_env());
	if (ft_strncmp(com[0], "exit", com_len) == 0)
		return(FAILURE);
	if (ft_strncmp(com[0], "export", com_len) == 0)
		return(exec_export(com));
	if (ft_strncmp(com[0], "pwd", com_len) == 0)
		return(exec_pwd());
	if (ft_strncmp(com[0], "unset", com_len) == 0)
		return(FAILURE);
	return (FAILURE);
}
