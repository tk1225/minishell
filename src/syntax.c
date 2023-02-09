#include "minishell.h"

int	syntax_check(t_tree *tree)
{
	if (tree->stat == COM && tree->len == 0)
		return(1);
	if (tree->left == NULL || tree->right == NULL)
		return (0);
	return (syntax_check(tree->left) + syntax_check(tree->right));
	// syntax_check(tree->right);
}
