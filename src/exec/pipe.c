/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:27:39 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/03 12:31:34 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	init_pipe(int pipe_count, int pipefd[4096][2])
{
	int	j;

	j = 0;
	while (j < pipe_count)
	{
		pipe(pipefd[j]);
		if (pipe == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		j ++;
	}
}

static	pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static	void	cat_pipe(int pipe_count, int pipefd[4096][2], int i)
{
	if (i >= 1)
		dup2(pipefd[i - 1][READ], STDIN_FILENO);
	if (pipe_count != i)
		dup2(pipefd[i][WRITE], STDOUT_FILENO);
	close_pipe(pipe_count, pipefd);
}

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

	i = pipe_count;
	init_pipe(pipe_count, pipefd);
	p_tree = tree;
	while (p_tree)
	{
		if (fork_process() == 0)
		{
			cat_pipe(pipe_count, pipefd, i);
			executer(next_com(p_tree), envp);
		}
		p_tree = p_tree->left;
		i--;
	}
	close_pipe(pipe_count, pipefd);
	return (0);
}
