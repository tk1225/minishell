/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:20:57 by atito             #+#    #+#             */
/*   Updated: 2023/03/05 14:22:59 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_redirect(char *com)
{
	if ((ft_strncmp(com, "<<", 3) == 0) || (ft_strncmp(com, ">>", 3) == 0) \
		|| (ft_strncmp(com, ">", 2) == 0) || (ft_strncmp(com, "<", 2) == 0))
		return (1);
	return (0);
}

static	int	syntax_redirect(char **com)
{
	int		i;
	char	*filename;

	i = 0;
	while (com[i])
	{
		if (is_redirect(com[i]))
		{
			filename = ft_strtrim(com[i + 1], "\"");
			if (filename == NULL || is_redirect(filename))
			{
				free(filename);
				return (1);
			}
			free(filename);
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
