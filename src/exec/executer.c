/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:19:53 by atito             #+#    #+#             */
/*   Updated: 2023/03/04 21:06:11 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	cnt = 0;
	while (dir[cnt] != NULL)
	{
		tmp = ft_strjoin(dir[cnt], "/");
		exec_path = ft_strjoin(tmp, com[0]);
		free(tmp);
		if (access(exec_path, X_OK) == 0)
			if (execve(exec_path, com, envp) == -1)
				exit(EXIT_FAILURE);
		cnt += 1;
		free(exec_path);
	}
	if (access(com[0], X_OK) == 0)
		if (execve(com[0], com, envp) == -1)
			exit(EXIT_FAILURE);
	free_lst(dir);
}

void	exe_com(char **com, t_env **env)
{
	char	*path;
	char	*path_copy;
	char	**dir;

	path = get_env("PATH", env);
	if (path == NULL)
	{
		perror("PATH environment variable not set");
		exit(EXIT_FAILURE);
	}
	path_copy = (char *)alloc_exit(sizeof(char), ft_strlen(path) + 1);
	ft_strlcpy(path_copy, path, ft_strlen(path));
	dir = ft_split(path_copy, ':');
	free(path_copy);
	exe_com_helper(com, dir, env);
}

int	executer(char **com, t_env **env)
{
	int	flag;

	if (recognize_redirect(com) == 1)
		exit (1);
	expansion(com, env);
	flag = builtin_set(com, env);
	if (flag == NONE)
		exe_com(com, env);
	else if (flag == FAILURE)
		g_status = 1;
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

	if ((tree->stat == COM) && (builtin_check(tree->com) == SUCCESS))
		return (exec_builtin(tree, env));
	set_signal_run();
	if (tree->stat == COM)
	{
		pid = fork_wrapper();
		if (pid == 0)
			executer(tree->com, env);
		wait(&status);
	}
	else
		status = exec_pipe(tree, env);
	if (g_status == 130 || g_status == 131)
		write(1, "\n", 1);
	return (WEXITSTATUS(status));
}
