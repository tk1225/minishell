#include "minishell.h"

void	free_lst(char **lst)
{
	size_t	cnt;

	cnt = 0;
	while (lst[cnt])
		free (lst[cnt++]);
	free (lst);
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->stat == COM)
		free_lst(tree->com);
	free(tree);
	tree = NULL;
}
