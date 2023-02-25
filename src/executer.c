#include "minishell.h"

extern int g_status_code;

static	void	exe_com_helper(char **com, char	**dir)
{
	int		i;
	char	*exec_path;
	char	*tmp;

	if (access(com[0], X_OK) == 0)
		execve(com[0], com, NULL);
	i = 0;
	while (dir[i] != NULL)
	{
		exec_path = ft_strjoin(dir[i], "/");
		tmp = exec_path;
		exec_path = ft_strjoin(exec_path, com[0]);
		free(tmp);
		if (access(exec_path, X_OK) == 0)
			execve(exec_path, com, NULL);
		i += 1;
		free(exec_path);
	}
}

int	exe_com(char **com, t_env **env)
{
	char	*path;
	char	*path_copy;
	char	**dir;

	path = getenvs("PATH", env);
	if (path == NULL)
	{
		perror("PATH environment variable not set");
		return (1);
	}
	path_copy = malloc(ft_strlen(path) + 1);
	ft_strlcpy(path_copy, path, ft_strlen(path));
	dir = ft_split(path_copy, ':');
	exe_com_helper(com, dir);
	return (0);
}

int	executer(char **com, t_env **env)
{
	recognize_redirect(com);
	expansion(com, env);
	if (exec_set(com, env) == FAILURE)
		exe_com(com, env);
	else
		exit(0);
	perror("command not found");
	exit(127);
	return (1);
}

int	exec_recursion(t_tree *tree, t_env **env)
{
	int	pid;
	int	status;
	int	original_stdin_fd;
	int	original_stdout_fd;

	if ((tree->stat == COM) && (exec_check(tree->com) == SUCCESS))
	{
		original_stdin_fd = dup(STDIN_FILENO);
		original_stdout_fd = dup(STDOUT_FILENO);
		recognize_redirect(tree->com);
		expansion(tree->com, env);
		if (exec_set(tree->com, env) != FAILURE)
		{
			dup2(original_stdin_fd, STDIN_FILENO);
			dup2(original_stdout_fd, STDOUT_FILENO);
			g_status_code = 0;
			return (0);
		}
		else
		{
			dup2(original_stdin_fd, STDIN_FILENO);
			dup2(original_stdout_fd, STDOUT_FILENO);
			g_status_code = 1;
			return (1);
		}
	}
	pid = fork();
	signal(SIGQUIT, handle_signals);
	if (pid == 0)
	{
		if (tree->stat == COM)
			executer(tree->com, env);
		handle_pipe(tree, env);
	}
	wait(&status);
	waitpid(pid, NULL, 0);
	if (g_status_code == 130 || g_status_code == 131)
		write(1, "\n", 1);
	g_status_code = WEXITSTATUS(status);
	return (status);
}
