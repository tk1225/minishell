#include "minishell.h"

char	*getenvs(char *key, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, ft_strlen(key) + 1) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
