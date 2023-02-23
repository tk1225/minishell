#include "minishell.h"

static int syntax_redirect(char **com)
{
	int i;
	char *filename;

	i = 0;
	while (com[i])
	{
		if ((ft_strncmp(com[i], "<<", 2) == 0) || (ft_strncmp(com[i], ">>", 2) == 0)\
			|| (ft_strncmp(com[i], ">", 1) == 0) || (ft_strncmp(com[i], "<", 1) == 0))
		{
			filename = ft_strtrim(com[i + 1], "\"");
			if (filename == NULL)
			{
				// perror("syntax error");
				return(1);
			}
		}
		i++;
	}
	return (0);
}

int	syntax_check(t_tree *tree)
{
	if (tree->stat == COM && tree->len == 0)
		return(1);
	if (tree->stat == COM)
	{
		if (syntax_redirect(tree->com) == 1)
			return (1);
	}
	if (tree->left == NULL || tree->right == NULL)
		return (0);
	return (syntax_check(tree->left) + syntax_check(tree->right));
}
