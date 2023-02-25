/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenvs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:33:25 by atito             #+#    #+#             */
/*   Updated: 2023/02/25 14:33:26 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getenvs(char *key, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, ft_strlen(key)) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
