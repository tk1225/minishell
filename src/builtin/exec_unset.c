#include "minishell.h"

int	exec_unset(char **com, t_env **env)
{
	t_env	*top;

	(void)com;
	if (!com[1])
		return (FAILURE);
	top = *env;
	while (top)
	{
		if (ft_strncmp(top->key, com[1], ft_strlen(com[1])) == 0)
		{
			top = top->prev;
			break ;
		}
		top = top->next;
	}
	if (top->next)
	{
		free(top->next->key);
		free(top->next->value);
		free(top->next);
		top->next = top->next->next;
	}
	return (SUCCESS);
}
