/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:27:17 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/03 12:27:32 by takumasaoka      ###   ########.fr       */
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
		tmp ++;
	}
}
