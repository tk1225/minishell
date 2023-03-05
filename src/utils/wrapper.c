/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:13:14 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/05 14:13:15 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	fork_wrapper(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork");
	return (pid);
}

int	dup_wrapper(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
		error_exit("dup");
	return (new_fd);
}

void	dup2_wrapper(int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
		error_exit("dup2");
}
