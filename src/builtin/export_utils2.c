/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:58:08 by atito             #+#    #+#             */
/*   Updated: 2023/03/05 15:58:29 by atito            ###   ########.fr       */
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
