#include "minishell.h"

void	free_lst(char **lst)
{
	while (*lst)
		free (*lst++);
	free (lst);
}
