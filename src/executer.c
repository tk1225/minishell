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
	perror("execve failed");
	return (0);
}

int	executer(char **com, char **envp)
{
	recognize_redirect(com);
	ft_expansion_dquote(com);
	ft_expansion_env(com);
	ft_expansion_squote(com);
	if (exec_set(com) == FAILURE)
		exe_com(com, envp);
	else
		exit(0);
	return (0);
}

int	exec_recursion(t_tree *tree, char **envp)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (tree->stat == COM)
			executer(tree->com, envp);
		handle_pipe(tree, envp);
	}
	wait(&status);
	waitpid(pid, NULL, 0);
	return(status);
}

//echo test | wc -l
//echo test | wc -l
