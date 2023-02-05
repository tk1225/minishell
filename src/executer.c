#include "minishell.h"
#include "exec.h"

int handle_redirect(char *target_filename, int stdfd, int append_flag)
{
	int fd;

	if (stdfd == WRITE)
	{
		if (append_flag == 1)
			fd = open(target_filename, O_RDWR | O_CREAT | O_APPEND);
		else
			fd = open(target_filename, O_RDWR | O_CREAT | O_TRUNC);
	}
	else
		fd = open(target_filename, O_RDWR | O_CREAT);

	if (fd == -1)
	{
    	perror("open");
    	return (1);
  	}
	int new_fd = dup(fd);
  	if (new_fd == -1)
	{
    	perror("dup");
    	return (1);
  	}
	close(stdfd);
	if (dup2(new_fd, stdfd) == -1)
	{
    	perror("dup2");
    	return (1);
  	}
	close(new_fd);
  	close(fd);
	return (new_fd);
}

int	exe_com(char **parsed_line, char **envp)
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
	return (0);
}

int	executer(char **parsed_line, char **envp)
{
	//parsed_lineの中で< > を見つけたらそのあとをファイル名として扱う
	// < と　その一つ後ろについては無視してコマンドを実行する 
	handle_redirect("sample.txt", WRITE, APPEND);
	// handle_redirect("sample.txt", READ);
	exe_com(parsed_line, envp);
	
	return (0);
}

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