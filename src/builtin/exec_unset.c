/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:19:49 by atito             #+#    #+#             */
/*   Updated: 2023/03/09 21:29:48 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(char **com, t_env **env)
{
	t_env	*top;
	t_env	*tmp;
	size_t	cnt;

	(void)com;
	cnt = 1;
	while (com[cnt])
	{
		ft_putstr_fd("com:", STDOUT_FILENO);
		ft_putendl_fd(com[cnt], STDOUT_FILENO);
		top = *env;
		while (top)
		{
			if (ft_strncmp(top->key, com[cnt], ft_strlen(com[cnt]) + 1) == 0)
			{
				top = top->prev;
				break ;
			}
			top = top->next;
		}
		ft_putendl_fd(top->next->key, STDOUT_FILENO);
		if (top)
		{
			free(top->next->key);
			free(top->next->value);
			tmp = top->next->next;
			free(top->next);
			top->next = tmp;
		}
		ft_putendl_fd(top->next->key, STDOUT_FILENO);
		cnt += 1;
	}
	return (SUCCESS);
}
