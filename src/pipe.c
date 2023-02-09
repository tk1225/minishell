#include "minishell.h"

int handle_pipe(t_tree *tree, char **envp)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (1);
	int pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(pipefd[WRITE], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (tree->left->stat == COM)
			executer(tree->left->com, envp);
		else if (tree->left->stat == PIPE)
			handle_pipe(tree->left, envp);
	}
	dup2(pipefd[READ], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	executer(tree->right->com, envp);
	waitpid(pid1, NULL, 0);
	return (0);
}
