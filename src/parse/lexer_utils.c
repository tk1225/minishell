/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:38:10 by atito             #+#    #+#             */
/*   Updated: 2023/03/02 20:38:11 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	judge_quote(int *quote, char c)
{
	if (c == '\"' && *quote == OUT_QUOTE)
		*quote = IN_DQUOTE;
	else if (c == '\"' && *quote == IN_DQUOTE)
		*quote = OUT_QUOTE;
	if (c == '\'' && *quote == OUT_QUOTE)
		*quote = IN_SQUOTE;
	else if (c == '\'' && *quote == IN_SQUOTE)
		*quote = OUT_QUOTE;
	return (*quote);
}

void	judge_char(char *c, int *quote, size_t *len)
{
	char	*space;
	char	*split;

	space = ft_strdup(" \t\n\v\f\r");
	split = ft_strdup(";()<>|&");
	*quote = judge_quote(quote, *c);
	if (ft_strchr(split, *c) && *c != *(c + 1))
		*len += 1;
	if (*quote == OUT_QUOTE && !ft_strchr("\'\"", *(c + 1)))
	{
		if (!ft_strchr(space, *c) && !ft_strchr(split, *c) && (!*(c + 1) || \
			ft_strchr(space, *(c + 1)) || ft_strchr(split, *(c + 1))))
			*len += 1;
	}
	free(space);
	free(split);
}
