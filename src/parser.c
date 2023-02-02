#include "minishell.h"

void print_tree(t_tree *tree)
{
	if (tree->left == NULL || tree->right == NULL)
		return;
	char **left_com = tree->left->com;
	char **right_com = tree->right->com;
	int left_len = tree->left->len;
	int right_len = tree->right->len;
	int i = 0;
	int j = 0;

	printf("leftlen%d\n", left_len);
	printf("rightlen%d\n-------\n", right_len);
	printf("leftnode\n");
	while (i < left_len)
		printf("%s\n", left_com[i++]);
	printf("rightnode\n");
	while (j < right_len)
		printf("%s\n", right_com[j++]);
	printf("\n");

	print_tree(tree->left);
	print_tree(tree->right);
}

t_tree *new_node()
{
	t_tree	*res;

	res = (t_tree *)alloc_exit(sizeof(t_tree) ,1);
	res->left = NULL;
	res->right = NULL;
	return (res);
}

void	split_by_semi(t_tree *tree, char **res, int len)
{
	int count;

	count = len;
	while (count--)
	{
		if (ft_strncmp(res[count], ";", 1) == 0)
		{
			tree->com = &res[count];
			tree->len = 1;
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

void	split_by_pipe(t_tree *tree)
{
	int count;

	count = tree->len;
	printf("node_len%d\n", count);
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
			tree->com = &tree->com[count];
			tree->len = 1;
			break ;
		}
	}
	if (tree->left)
		split_by_pipe(tree->left);
	if (tree->right)
		split_by_pipe(tree->right);
}

char **parser(char *line)
{
	char	**res;
	t_tree	**tree;

	res = lexer(line);
	int i = 0;
	while (1)
	{
		if (!res[i])
			break ;
		i += 1;
	}
	tree = (t_tree **)alloc_exit(sizeof(t_tree *), 1);
	*tree = new_node();
	split_by_semi(*tree, res, i);
	split_by_pipe(*tree);
	print_tree(*tree);
	return (res);
}
