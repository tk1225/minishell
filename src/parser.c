#include "minishell.h"

//delete
void	print_tree(t_tree *tree)
{
	printf("node len%zu\n", tree->len);
	printf("node stat%d\n", tree->stat);
	for (size_t i = 0; i < tree->len; i++)
		printf("command %s\n", tree->com[i++]);
	if (tree->right != NULL)
		print_tree(tree->right);
	if (tree->left != NULL)
		print_tree(tree->left);
	return ;
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
			split_by_pipe(tree->left);
			break ;
		}
	}
}

t_tree	**parser(char **res)
{
	// char	**res;
	t_tree	**tree;
	size_t	cnt;

	// res = lexer(line);
	cnt = 0;
	while (res[cnt])
	{
		// printf("%s\n", res[cnt]);
		cnt += 1;

	}
		// printf("%s\n", res[cnt++]);

	tree = (t_tree **)alloc_exit(sizeof(t_tree *), 1);
	*tree = new_node();
	(*tree)->com = res;
	(*tree)->len = cnt;
	split_by_pipe(*tree);
	// if (syntax_check(*tree) > 0)
	// 	perror("syntax error");
	return (tree);
}
