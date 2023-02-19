#include "minishell.h"

int	exec_unset(char **com, char **envp)
{
	size_t	cnt;


	(void)com;
	cnt = 0;
	if (!com[1])
		return (FAILURE);
	while (envp[cnt])
	{
		if (ft_strncmp(envp[cnt], ft_strjoin(com[1], "="), ft_strlen(com[1]) + 1) == 0)
			break ;
		cnt += 1;
	}
	while (envp[cnt])
	{
		envp[cnt] = envp[cnt + 1];
		cnt += 1;
	}
	return (SUCCESS);
}
