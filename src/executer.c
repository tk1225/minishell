#include "minishell.h"
#include "exec.h"

int	executer(int argc, char **parsed_line, char **envp)
{
char	*command_path;
pid_t	pid;
int		status;

command_path = ft_strjoin("/bin/", parsed_line[0]);
(void)argc;
pid = fork();
if (-1 == pid)
	err (EXIT_FAILURE, "can not fork");
else if (0 == pid)
{
	//子プロセス
	if (execve(command_path, parsed_line, envp) == -1){}
		exit(EXIT_SUCCESS);
}
else
{
	//親プロセス
	wait(&status);
	//ゾンビプロセス回避
	waitpid(pid, &status, 0);
}
return (0);
}

void	exec_tree(t_tree *tree, char **envp)
{
	size_t k;

	k = 0;
	if (tree == NULL)
		return;
	exec_tree(tree->left, envp);
	printf("this node\n");
	while (k < tree->len)
		printf("%s\n", tree->com[k++]);
	executer(tree->len, tree->com, envp);
	exec_tree(tree->right, envp);
	// char **left_com = tree->left->com;
	// char **right_com = tree->right->com;
	// size_t left_len = tree->left->len;
	// size_t right_len = tree->right->len;
	// size_t i = 0;
	// size_t j = 0;

	// printf("leftlen%zu\n", left_len);
	// printf("rightlen%zu\n-------\n", right_len);
	// printf("leftnode\n");
	// while (i < left_len)
	// 	printf("%s\n", left_com[i++]);
	// printf("rightnode\n");
	// while (j < right_len)
	// 	printf("%s\n", right_com[j++]);
	printf("\n");
}
