#include "minishell.h"

//delete
void	print_tree(t_tree *tree)
{
	size_t k = 0;
	printf("this node\n");
	printf("this node%zu\n", tree->len);
	while (k < tree->len)
		printf("%s\n", tree->com[k++]);
	if (tree->left == NULL || tree->right == NULL)
		return;
	print_tree(tree->left);
	print_tree(tree->right);
}

static t_tree	*new_node()
{
	t_tree	*res;

	res = (t_tree *)alloc_exit(sizeof(t_tree) ,1);
	res->left = NULL;
	res->right = NULL;
	res->com = NULL;
	res->stat = COM;
	return (res);
}

static void	split_by_semi(t_tree *tree, char **res, size_t len)
{
	size_t	count;

	count = len;
	while (count--)
	{
		if (ft_strncmp(res[count], ";", 1) == 0)
		{
			free(res[count]);
			res[count] = NULL;
			tree->com = NULL;
			tree->len = 0;
			tree->stat = SEMICOL;
			tree->left = new_node();
			tree->left->len = count;
			tree->left->com = &res[0];
			tree->right = new_node();
			tree->right->len = len - count - 1;
			tree->right->com = &res[count + 1];
			split_by_semi(tree->left, res, count);
			break ;
		}
	}
}

static void	split_by_pipe(t_tree *tree)
{
	size_t count;

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
			break ;
		}
	}
	if (tree->left)
		split_by_pipe(tree->left);
	if (tree->right)
		split_by_pipe(tree->right);
}

t_tree	**parser(char *line)
{
	char	**res;
	t_tree	**tree;
	size_t	cnt;

	res = lexer(line);
	cnt = 0;
	while (res[cnt])
		cnt += 1;
	tree = (t_tree **)alloc_exit(sizeof(t_tree *), 1);
	*tree = new_node();
	split_by_semi(*tree, res, cnt);
	if ((*tree)->stat == COM)
	{
		(*tree)->com = res;
		(*tree)->len = cnt;
	}
	split_by_pipe(*tree);
	return (tree);
}
