/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:44:31 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/13 22:51:56 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	builtin_check(char **com)
{
	size_t	com_len;

	com_len = ft_strlen(com[0]) + 1;
	if (ft_strncmp(com[0], "cd", com_len) == 0)
		return (SUCCESS);
	else if (ft_strncmp(com[0], "echo", com_len) == 0)
		return (SUCCESS);
	else if (ft_strncmp(com[0], "env", com_len) == 0)
		return (SUCCESS);
	else if (ft_strncmp(com[0], "exit", com_len) == 0)
		return (SUCCESS);
	else if (ft_strncmp(com[0], "export", com_len) == 0)
		return (SUCCESS);
	else if (ft_strncmp(com[0], "pwd", com_len) == 0)
		return (SUCCESS);
	else if (ft_strncmp(com[0], "unset", com_len) == 0)
		return (SUCCESS);
	return (NONE);
}

int	exec_builtin(t_tree *tree, t_env **env)
{
	int	original_stdin_fd;
	int	original_stdout_fd;

	original_stdin_fd = dup_wrapper(STDIN_FILENO);
	original_stdout_fd = dup_wrapper(STDOUT_FILENO);
	if (recognize_redirect(tree->com) == 1)
	{
		dup2_wrapper(original_stdin_fd, STDIN_FILENO);
		dup2_wrapper(original_stdout_fd, STDOUT_FILENO);
		return (1);
	}
	expansion(tree->com, env);
	if (builtin_set(tree->com, env) != FAILURE)
	{
		dup2_wrapper(original_stdin_fd, STDIN_FILENO);
		dup2_wrapper(original_stdout_fd, STDOUT_FILENO);
		return (0);
	}
	else
	{
		dup2_wrapper(original_stdin_fd, STDIN_FILENO);
		dup2_wrapper(original_stdout_fd, STDOUT_FILENO);
		return (1);
	}
}
