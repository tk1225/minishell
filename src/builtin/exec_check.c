/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:32:51 by atito             #+#    #+#             */
/*   Updated: 2023/02/25 14:32:52 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_check(char **com)
{
	size_t	com_len;

	com_len = ft_strlen(com[0]);
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
	return (FAILURE);
}
