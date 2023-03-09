/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:19:27 by atito             #+#    #+#             */
/*   Updated: 2023/03/09 19:36:54 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(char **com, t_env **env)
{
	t_env	*top;

	(void)com;
	top = *env;
	while (top)
	{
		if (top->key && top->value)
		{
			ft_putstr_fd(top->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(top->value, STDOUT_FILENO);
		}
		top = top->next;
	}
	return (SUCCESS);
}
