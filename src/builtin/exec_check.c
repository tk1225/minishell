#include "minishell.h"

int	exec_check(char **com)
{
	size_t	com_len;

	com_len = ft_strlen(com[0]);
	if (ft_strncmp(com[0], "cd", com_len) == 0)
		return(SUCCESS);
	else if (ft_strncmp(com[0], "echo", com_len) == 0)
		return(SUCCESS);
	else if (ft_strncmp(com[0], "env", com_len) == 0)
		return(SUCCESS);
	else if (ft_strncmp(com[0], "exit", com_len) == 0)
		return(SUCCESS);
	else if (ft_strncmp(com[0], "export", com_len) == 0)
		return(SUCCESS);
	else if (ft_strncmp(com[0], "pwd", com_len) == 0)
		return(SUCCESS);
	else if (ft_strncmp(com[0], "unset", com_len) == 0)
		return(SUCCESS);
	return (FAILURE);
}
