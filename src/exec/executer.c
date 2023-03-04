/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:39:28 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/04 15:10:49 by takuokam         ###   ########.fr       */
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
	if (recognize_redirect(com) == 1)
		exit (1);
	expansion(com, env);
	if (builtin_set(com, env) == NONE)
		exe_com(com, env);
	else
		exit(0);
	error_exit("command not found");
	exit(127);
	return (1);
}

int	exec_recursion(t_tree *tree, t_env **env)
{
	int	pid;
	int	status;

	if ((tree->stat == COM) && (builtin_check(tree->com) == SUCCESS))
		return (exec_builtin(tree, env));
	signal(SIGQUIT, handle_signals);
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
