/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:38:13 by atito             #+#    #+#             */
/*   Updated: 2023/03/02 20:38:14 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	judge_insert(char const *s, int *quote, size_t *cnt)
{
	char	*space;
	char	*split;
	int		flag;

	space = ft_strdup(" \t\n\v\f\r");
	split = ft_strdup(";()<>|&");
	flag = 0;
	if (*quote == OUT_QUOTE && s[*cnt] != s[*cnt + 1] && \
		ft_strchr(split, s[*cnt]))
		flag = 1;
	else if (*quote == OUT_QUOTE && !ft_strchr("\'\"", s[*cnt + 1]))
	{
		if ((!ft_strchr(space, s[*cnt]) && \
			!ft_strchr(split, s[*cnt]) && (!s[*cnt + 1] || \
			ft_strchr(space, s[*cnt + 1]) || \
			ft_strchr(split, s[*cnt + 1]))) || \
			(ft_strchr(split, s[*cnt]) && \
			!ft_strchr(split, s[*cnt + 1])))
			flag = 1;
	}
	free(space);
	free(split);
	*cnt += 1;
	return (flag);
}

static void	insert_word(char **lst, char const *s)
{
	size_t	cnt;
	size_t	len;
	int		quote;
	char	*space;
	char	*split;

	space = ft_strdup(" \t\n\v\f\r");
	split = ft_strdup(";()<>|&");
	cnt = 0;
	len = 0;
	quote = OUT_QUOTE;
	while (s[cnt])
	{
		quote = judge_quote(&quote, s[cnt]);
		if (!(quote == OUT_QUOTE && ft_strchr(space, s[cnt])))
			len += 1;
		if (judge_insert(s, &quote, &cnt) == 1)
		{
			*lst++ = ft_substr(s, cnt - len, len);
			len = 0;
		}
	}
	free(space);
	free(split);
	*lst = NULL;
}

static size_t	count_word(char *s)
{
	size_t	cnt;
	size_t	len;
	int		quote;

	cnt = 0;
	len = 0;
	quote = OUT_QUOTE;
	while (s[cnt])
	{
		judge_char(&s[cnt], &quote, &len);
		cnt += 1;
	}
	if (quote == IN_SQUOTE || quote == IN_DQUOTE)
		error_exit("quote error");
	return (len);
}

char	**lexer(char *str)
{
	char	**lst;
	size_t	len;

	if (!str)
		return (NULL);
	len = count_word(str);
	lst = (char **)alloc_exit(sizeof(char *), (len + 1));
	insert_word(lst, str);
	return (lst);
}
