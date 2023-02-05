#include "minishell.h"
#include "exec.h"

// void	exec_tree(t_tree *tree, char **envp)
// {
// 	size_t k;
// 	k = 0;
// 	if (tree == NULL)
// 		return;
// 	exec_tree(tree->left, envp);
// 	printf("-----\n");
// 	if (tree->com)
// 		printf("this node\n");
// 	while (k < tree->len)
// 		printf("%s\n", tree->com[k++]);
// 	printf("-----\n");
// 	if (tree->com)
// 		executer(tree->len, tree->com, envp);
// 	exec_tree(tree->right, envp);
// }

// int	executer(char **parsed_line, char **envp)
// {
// 	char	*command_path;

// 	command_path = ft_strjoin("/bin/", parsed_line[0]);
// 	if (execve(command_path, parsed_line, envp) == -1)
// 		exit(EXIT_SUCCESS);
// 	return (0);
// }

int	executer(char **parsed_line, char **envp)
{
	char *path = getenv("PATH");
	if (path == NULL) {
		perror("PATH environment variable not set");
		return 1;
	}
	size_t path_len = ft_strlen(path);
	char *path_copy = malloc(path_len + 1);
	strcpy(path_copy, path);
	char *dir = strtok(path_copy, ":");
	while (dir != NULL) {
		char exec_path[1024];
		snprintf(exec_path, sizeof(exec_path), "%s/%s", dir, parsed_line[0]);
		if (access(exec_path, X_OK) == 0) {
			execve(exec_path, parsed_line, envp);
		}
		dir = strtok(NULL, ":");
	}
	perror("execve failed");
	return 1;
	return (0);
}

// int handle_pipe(t_tree *tree, char **envp)
// {
// 	int pipefd[2];
// 	if (pipe(pipefd) == -1)
// 		return (1);
// 	int pid1 = fork();
// 	if (pid1 < 0)
// 		return (2);
// 	if (pid1 == 0)
// 	{
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		executer(tree->left->com, envp);
// 	}
// 	int pid2 = fork();
// 	if (pid2 < 0)
// 		return (3);
// 	if (pid2 == 0)
// 	{
// 		dup2(pipefd[0], STDIN_FILENO);
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		executer(tree->right->com, envp);
// 	}
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }

// int handle_semicolon(t_tree *tree, char **envp)
// {
// 	int pid1 = fork();
// 	if (pid1 < 0)
// 		return (2);
// 	if (pid1 == 0)
// 		executer(tree->left->com, envp);
// 	int pid2 = fork();
// 	if (pid2 < 0)
// 		return (3);
// 	if (pid2 == 0)
// 		executer(tree->right->com, envp);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return(0);
// }

int handle_pipe(t_tree *tree, char **envp)
{
	int pipefd[2];
	if (pipe(pipefd) == -1)
		return (1);
	int pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (tree->left->stat == COM)
			executer(tree->left->com, envp);
		else if (tree->left->stat == PIPE)
			handle_pipe(tree->left, envp);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	executer(tree->right->com, envp);
	waitpid(pid1, NULL, 0);
	return (0);
}

int	exec_recursion(t_tree *tree, char **envp)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (tree->stat == COM)
			executer(tree->com, envp);
		handle_pipe(tree, envp);
	}
	waitpid(pid, NULL, 0);
	return(0);
}

//echo test | wc -l
//ls | head | wc -l