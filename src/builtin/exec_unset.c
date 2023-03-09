/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:19:49 by atito             #+#    #+#             */
/*   Updated: 2023/03/09 12:25:30 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(char **com, t_env **env)
{
	t_env	*top;
	size_t	cnt;

	(void)com;
	cnt = 1;
	while (com[cnt])
	{
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
		if (top)
		{
			free(top->next->key);
			free(top->next->value);
			free(top->next);
			top->next = top->next->next;
		}
		cnt += 1;
	}
	return (SUCCESS);
}
