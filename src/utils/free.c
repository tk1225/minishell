#include "minishell.h"

void	free_lst(char **lst)
{
	int	i;

	i = 0;
	while (lst[i] != NULL)
		free (lst[i++]);
	free (lst);
}

void	free_tree(t_tree *tree)
{
	if (tree->com == NULL)
		return ;
	free_lst(tree->com);
	if (tree->right)
		free_tree(tree->right);
	if (tree->left)
		free_tree(tree->left);
}
