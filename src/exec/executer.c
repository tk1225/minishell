#include "minishell.h"

extern int	g_status;

static char	**convert_envs(t_env **env)
{
	t_env	*tmp;
	char	*node;
	char	**envp;
	size_t	env_len;
	size_t	cnt;

	env_len = 0;
	tmp = *env;
	while (tmp)
	{
		env_len ++;
		tmp = tmp->next;
	}
	tmp = *env;
	envp = (char **)alloc_exit(sizeof(char **), env_len + 1);
	cnt = 0;
	while (tmp)
	{
		node = join_three(tmp->key, "=", tmp->value);
		envp[cnt] = node;
		tmp = tmp->next;
		cnt++;
	}
	envp[cnt] = NULL;
	return (envp);
}

static	void	exe_com_helper(char **com, char	**dir, t_env **env)
{
	int		cnt;
	char	*exec_path;
	char	*tmp;
	char	**envp;

	envp = convert_envs(env);
	(void)env;
	if (access(com[0], X_OK) == 0)
		execve(com[0], com, envp);
	cnt = 0;
	while (dir[cnt] != NULL)
	{
		tmp = ft_strjoin(dir[cnt], "/");
		exec_path = ft_strjoin(tmp, com[0]);
		free(tmp);
		if (access(exec_path, X_OK) == 0)
			execve(exec_path, com, envp);
		cnt += 1;
		free(exec_path);
	}
	free_lst(dir);
}

int	exe_com(char **com, t_env **env)
{
	char	*path;
	char	*path_copy;
	char	**dir;

	path = get_env("PATH", env);
	if (path == NULL)
	{
		error_exit("PATH environment variable not set");
		return (1);
	}
	path_copy = (char *)alloc_exit(sizeof(char), ft_strlen(path) + 1);
	ft_strlcpy(path_copy, path, ft_strlen(path));
	dir = ft_split(path_copy, ':');
	free(path_copy);
	exe_com_helper(com, dir, env);
	return (0);
}

int	executer(char **com, t_env **env)
{
	recognize_redirect(com);
	expansion(com, env);
	if (builtin_set(com, env) == NONE)
		exe_com(com, env);
	else
		exit(0);
	error_exit("command not found");
	exit(127);
	return (1);
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		// wait_result = waitpid(-last_pid, &wstatus, 0);
		if (wait_result == last_pid)
			status = WEXITSTATUS(wstatus);
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	return (status);
}

int	exec_recursion(t_tree *tree, t_env **env)
{
	int	pid;
	int	status;

	if ((tree->stat == COM) && (builtin_check(tree->com) == SUCCESS))
		return (exec_builtin(tree, env));
	pid = fork();
	signal(SIGQUIT, handle_signals);
	if (pid == 0)
	{
		if (tree->stat == COM)
			executer(tree->com, env);
		exit(0);
	}
	int pipe_count;
    pipe_count = count_pipe(tree);
    if (pipe_count != 0)
		handle_pipe(tree, env, pipe_count);
	wait_pipeline(pid);
	// wait(&status);
	// waitpid(pid, NULL, 0);
	if (g_status == 130 || g_status == 131)
		write(1, "\n", 1);
	g_status = WEXITSTATUS(status);
	return (status);
}
