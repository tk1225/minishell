/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:58:08 by atito             #+#    #+#             */
/*   Updated: 2023/03/14 13:47:03 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_env(t_env **top, char *value)
{
	char	*tmp;

	tmp = value;
	value = ft_strjoin((*top)->value, tmp);
	free(tmp);
	return (value);
}

int	is_valid_key(char *key)
{
	if (ft_isdigit(key[0]) || ft_strlen(key) == 0)
		return (1);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (1);
		key += 1;
	}
	return (0);
}
