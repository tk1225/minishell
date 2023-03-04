/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:27:17 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/04 22:55:10 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(t_tree *tree)
{
	if (tree->stat == PIPE)
		return (1 + count_pipe(tree->left) + count_pipe(tree->right));
	else
		return (0);
}

void	close_pipe(int pipe_count, int pipefd[4096][2])
{
	int	tmp;

	tmp = 0;
	while (tmp < pipe_count)
	{
		close(pipefd[tmp][0]);
		close(pipefd[tmp][1]);
		// if (close(pipefd[tmp][0]) == -1)
		// 	exit(EXIT_FAILURE);
		// if (close(pipefd[tmp][1]) == -1)
		// 	exit(EXIT_FAILURE);
		tmp += 1;
	}
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
			status = wstatus;
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	return (status);
}

void	init_pipe(int pipe_count, int pipefd[4096][2])
{
	int	j;

	j = 0;
	while (j < pipe_count)
	{
		if (pipe(pipefd[j]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		j ++;
	}
}

void	cat_pipe(int pipe_count, int pipefd[4096][2], int i)
{
	if (i >= 1)
		dup2_wrapper(pipefd[i - 1][READ], STDIN_FILENO);
	if (pipe_count != i)
		dup2_wrapper(pipefd[i][WRITE], STDOUT_FILENO);
	close_pipe(pipe_count, pipefd);
}
