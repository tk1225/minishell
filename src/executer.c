#include "minishell.h"

int	exe_com(char **com, char **envp)
{
	char *path;

	path = getenv("PATH");
	if (path == NULL) {
		perror("PATH environment variable not set");
		return (1);
	}
	size_t path_len = ft_strlen(path);
	char *path_copy = malloc(path_len + 1);
	ft_strlcpy(path_copy, path, ft_strlen(path));
	char **dir = ft_split(path_copy, ':');
	int i = 0;
	while (dir[i] != NULL)
	{
		char *exec_path;
		char *tmp;

		exec_path = ft_strjoin(dir[i], "/");
		tmp = exec_path;
		exec_path = ft_strjoin(exec_path, com[0]);
		free(tmp);
		if (access(exec_path, X_OK) == 0)
			execve(exec_path, com, envp);
		i ++;
		free(exec_path);
	}
	return (0);
}

int	executer(char **com, char **envp)
{
	recognize_redirect(com);
	expansion(com);
	if (exec_set(com, envp) == FAILURE)
		exe_com(com, envp);
	else
		exit(0);
	perror("command not found");
	exit(127);
	return (1);

}

int	exec_recursion(t_tree *tree, char **envp)
{
	int pid;
	int status;
	
	if (tree->stat == COM)
	{
		recognize_redirect(tree->com);
		expansion(tree->com);
		if (exec_set(tree->com, envp) != FAILURE)
			return (0);
	}
	pid = fork();
	if (pid == 0)
		handle_pipe(tree, envp);
	wait(&status);
	waitpid(pid, NULL, 0);
	return(status);
}
