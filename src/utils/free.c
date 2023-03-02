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
	size_t	cnt;

	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->stat == COM)
	{
		cnt = 0;
		while (tree->com[cnt])
			free(tree->com[cnt++]);
	}
	free(tree);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;;
	}
}
