/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:19:49 by atito             #+#    #+#             */
/*   Updated: 2023/03/12 02:46:56 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_top(t_env **env, t_env *top)
{
	top = top->next;
	free(top->prev->key);
	free(top->prev->value);
	free(top->prev);
	top->prev = NULL;
	*env = top;
}

static void	delete_end(t_env *top)
{
	top = top->prev;
	free(top->next->key);
	free(top->next->value);
	free(top->next);
	top->next = NULL;
}

static void	delete_middle(t_env *top)
{
	t_env	*tmp;

	tmp = top->next;
	top = top->prev;
	free(top->next->key);
	free(top->next->value);
	free(top->next);
	top->next = tmp;
	tmp->prev = top;
}

int	exec_unset(char **com, t_env **env)
{
	t_env	*top;
	size_t	cnt;

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
		if (top && !(top->prev))
			delete_top(env, top);
		else if (top && !(top->next))
			delete_end(top);
		else if (top)
			delete_middle(top);
		cnt += 1;
	}
	return (SUCCESS);
}
