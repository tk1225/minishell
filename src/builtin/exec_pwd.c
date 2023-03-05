/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:19:45 by atito             #+#    #+#             */
/*   Updated: 2023/03/05 13:19:45 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(char **com, t_env **env)
{
	char	cwd[PATH_MAX];

	(void)com;
	(void)env;
	if (!getcwd(cwd, PATH_MAX))
		return (FAILURE);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (SUCCESS);
}
