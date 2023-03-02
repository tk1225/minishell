#include "minishell.h"

static void	insert_word(char **lst, char const *s)
{
	size_t	cnt;
	size_t	len;
	int		s_quote;
	int		d_quote;

	cnt = 0;
	len = 0;
	s_quote = OUT_QUOTE;
	d_quote = OUT_QUOTE;
	while (s[cnt])
	{
		if (s[cnt] == '\"' && s_quote == OUT_QUOTE)
			d_quote *= -1;
		if (s[cnt] == '\'' && d_quote == OUT_QUOTE)
			s_quote *= -1;
		if (!(ft_strchr(" \t\n\v\f\r", s[cnt]) && \
			d_quote == OUT_QUOTE && s_quote == OUT_QUOTE))
			len += 1;
		if (ft_strchr(";()<>|&", s[cnt]) && s[cnt] != s[cnt + 1] && \
			d_quote == OUT_QUOTE && s_quote == OUT_QUOTE)
		{
			*lst = ft_substr(s, cnt - len + 1, len);
			if (!*lst++)
			{
				free_lst(lst);
				return ;
			}
			len = 0;
		}
		else if (d_quote == OUT_QUOTE && s_quote == OUT_QUOTE && \
			!ft_strchr("\'\"", s[cnt + 1]))
		{
			if ((!ft_strchr(" \t\n\v\f\r", s[cnt]) && \
				!ft_strchr(";()<>|&", s[cnt]) && (!s[cnt + 1] || \
				ft_strchr(" \t\n\v\f\r;()<>|&", s[cnt + 1]))) || \
				(ft_strchr(";()<>|&", s[cnt]) && \
				!ft_strchr(";()<>|&", s[cnt + 1])))
			{
				*lst = ft_substr(s, cnt - len + 1, len);
				if (!*lst++)
				{
					free_lst(lst);
					return ;
				}
				len = 0;
			}
		}
		cnt += 1;
	}
	*lst = NULL;
}

void	judge_char(char *c, int *s_quote, int *d_quote, size_t *len)
{
	char	*space;
	char	*split;

	space = ft_strdup(" \t\n\v\f\r");
	split = ft_strdup(";()<>|&");
	if (*c == '\"' && *s_quote == OUT_QUOTE)
		*d_quote *= -1;
	if (*c == '\'' && *d_quote == OUT_QUOTE)
		*s_quote *= -1;
	if (ft_strchr(split, *c) && *c != *(c + 1))
		*len += 1;
	if (*d_quote == OUT_QUOTE && *s_quote == OUT_QUOTE && \
		!ft_strchr("\'\"", *(c + 1)))
	{
		if (!ft_strchr(space, *c) && !ft_strchr(split, *c) && (!*(c + 1) || \
			ft_strchr(space, *(c + 1)) || ft_strchr(split, *(c + 1))))
			*len += 1;
	}
	free(space);
	free(split);
}

static size_t	count_word(char *s)
{
	size_t	cnt;
	size_t	len;
	int		s_quote;
	int		d_quote;

	cnt = 0;
	len = 0;
	s_quote = OUT_QUOTE;
	d_quote = OUT_QUOTE;
	while (s[cnt])
	{
		judge_char(&s[cnt], &s_quote, &d_quote, &len);
		cnt += 1;
	}
	if (d_quote == IN_QUOTE || s_quote == IN_QUOTE)
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
