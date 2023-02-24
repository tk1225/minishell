#include "minishell.h"

int	handle_pipe(t_tree *tree, t_env **envp)
{
	int	pipefd[2];
	int	pid;
	int	status;

	if (pipe(pipefd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
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
	wait(&status);
	executer(tree->right->com, envp);
	return (0);
}
