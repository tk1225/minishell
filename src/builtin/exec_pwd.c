/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:33:07 by atito             #+#    #+#             */
/*   Updated: 2023/02/25 14:33:08 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(char **com, t_env **env)
{
	char	path[512];

	(void)com;
	(void)env;
	getcwd(path, sizeof(path));
	ft_putendl_fd(path, 1);
	return (SUCCESS);
}
