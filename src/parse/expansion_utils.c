/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:38:05 by atito             #+#    #+#             */
/*   Updated: 2023/03/02 20:38:06 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_dollar(t_env **env, char **str, char *prm)
{
	char		*tmp;
	char		*s2;
	char		*s3;
	extern int	g_status;

	if (prm[0] == '\0')
		tmp = ft_strjoin(*str, "$");
	else if (prm[0] == '?')
	{
		s2 = ft_itoa(g_status);
		s3 = ft_substr(prm, 1, ft_strlen(prm) - 1);
		tmp = join_three(*str, s2, s3);
		free(s2);
		free(s3);
	}
	else
	{
		s2 = get_env(prm, env);
		tmp = ft_strjoin(*str, s2);
		free(s2);
	}
	return (tmp);
}
