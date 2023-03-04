/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 00:24:08 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/04 11:53:07 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	syntax_redirect(char **com)
{
	int		i;
	char	*filename;

	i = 0;
	while (com[i])
	{
		if ((ft_strncmp(com[i], "<<", 3) == 0) || \
		(ft_strncmp(com[i], ">>", 3) == 0) \
			|| (ft_strncmp(com[i], ">", 2) == 0) \
			|| (ft_strncmp(com[i], "<", 2) == 0))
		{
			filename = ft_strtrim(com[i + 1], "\"");
			if (filename == NULL)
				return (1);
		}
		i++;
	}
	return (0);
}

int	syntax_check(t_tree *tree)
{
	if (tree->stat == COM && tree->len == 0)
		return (1);
	if (tree->stat == COM)
	{
		if (syntax_redirect(tree->com) == 1)
			return (1);
	}
	if (tree->left == NULL || tree->right == NULL)
		return (0);
	return (syntax_check(tree->left) + syntax_check(tree->right));
}
