/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:27:39 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/03 14:39:03 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**next_com(t_tree *p_tree)
{
	char	**com;

	if (p_tree->stat == COM)
		com = p_tree->com;
	else
		com = p_tree->right->com;
	return (com);
}

int	handle_pipe(t_tree *tree, t_env **envp, int pipe_count)
{
	int		pipefd[4096][2];
	int		i;
	t_tree	*p_tree;
	pid_t	last_pid;
	pid_t	pid;

	i = pipe_count;
	init_pipe(pipe_count, pipefd);
	p_tree = tree;
	while (p_tree)
	{
		pid = fork_wrapper();
		if (i == pipe_count)
			last_pid = pid;
		if (pid == 0)
		{
			cat_pipe(pipe_count, pipefd, i);
			executer(next_com(p_tree), envp);
		}
		p_tree = p_tree->left;
		i--;
	}
	close_pipe(pipe_count, pipefd);
	return (last_pid);
}

int	exec_pipe(t_tree *tree, t_env **envp)
{
	int		pipe_count;
	pid_t	pid;
	int		status;

	pipe_count = count_pipe(tree);
	pid = handle_pipe(tree, envp, pipe_count);
	status = wait_pipeline(pid);
	return (status);
}
