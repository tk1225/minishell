#include "minishell.h"

static t_tree	*new_node(void)
{
	t_tree	*res;

	res = (t_tree *)alloc_exit(sizeof(t_tree), 1);
	res->left = NULL;
	res->right = NULL;
	res->com = NULL;
	res->stat = COM;
	return (res);
}

static void	split_by_pipe(t_tree *tree)
{
	size_t	count;

	count = tree->len;
	while (count--)
	{
		if (ft_strncmp(tree->com[count], "|", 1) == 0)
		{
			tree->left = new_node();
			tree->left->len = count;
			tree->left->com = &tree->com[0];
			tree->right = new_node();
			tree->right->len = tree->len - count - 1;
			tree->right->com = &tree->com[count + 1];
			free(tree->com[count]);
			tree->com[count] = NULL;
			tree->com = NULL;
			tree->len = 0;
			tree->stat = PIPE;
			split_by_pipe(tree->left);
			break ;
		}
	}
}

t_tree	**parser(char **res)
{
	t_tree	**tree;
	size_t	cnt;

	cnt = 0;
	while (res[cnt])
		cnt += 1;
	tree = (t_tree **)alloc_exit(sizeof(t_tree *), 1);
	*tree = new_node();
	(*tree)->com = res;
	(*tree)->len = cnt;
	split_by_pipe(*tree);
	return (tree);
}
