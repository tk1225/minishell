/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:19:49 by atito             #+#    #+#             */
/*   Updated: 2023/03/11 21:35:14 by atito            ###   ########.fr       */
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
		top = *env;
		while (top)
		{
			if (ft_strncmp(top->key, com[cnt], ft_strlen(com[cnt]) + 1) == 0)
				break ;
			top = top->next;
		}
		printf("test0\n");
		if (top && !(top->prev))
		{
			printf("test1\n");
			top = top->next;
			free(top->prev->key);
			free(top->prev->value);
			free(top->prev);
			top->prev = NULL;
			*env = top;
		}
		else if (top && !(top->next))
		{
			printf("test2\n");
			top = top->prev;
			free(top->next->key);
			free(top->next->value);
			free(top->next);
			top->next = NULL;
		}
		else if (top)
		{
			printf("test3\n");
			tmp = top->next;
			top = top->prev;
			free(top->next->key);
			free(top->next->value);
			free(top->next);
			top->next = tmp;
		}
		cnt += 1;
	}
	return (SUCCESS);
}
