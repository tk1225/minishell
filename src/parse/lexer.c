#include "minishell.h"

static void	insert_word(char **lst, char const *s, char *c, char *o)
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
		if (s[cnt] == '\"')
			d_quote *= -1;
		if (s[cnt] == '\'')
			s_quote *= -1;
		if (!(ft_strchr(c, s[cnt]) && d_quote == OUT_QUOTE && s_quote == OUT_QUOTE))
			len += 1;
		if (ft_strchr(o, s[cnt]) && s[cnt] != s[cnt + 1] && d_quote == 1 && s_quote == 1)
		{
			*lst = ft_substr(s, cnt - len + 1, len);
			if (!*lst++)
			{
				free_lst(lst);
				return ;
			}
			len = 0;
		}
		else if (d_quote == OUT_QUOTE && s_quote == OUT_QUOTE && !ft_strchr("\'\"", s[cnt + 1]))
		{
			if ((!ft_strchr(c, s[cnt]) && !ft_strchr(o, s[cnt]) && (!s[cnt + 1] || ft_strchr(c, s[cnt + 1]) || ft_strchr(o, s[cnt + 1]))) || (ft_strchr(o, s[cnt]) && !ft_strchr(o, s[cnt + 1])))
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

static size_t	count_word(char const *s, char *c, char *o)
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
		if (s[cnt] == '\"')
			d_quote *= -1;
		if (s[cnt] == '\'')
			s_quote *= -1;
		if (ft_strchr(o, s[cnt]) && s[cnt] != s[cnt + 1])
			len += 1;
		if (d_quote == OUT_QUOTE && s_quote == OUT_QUOTE && !ft_strchr("\'\"", s[cnt + 1]))
		{
			if (!ft_strchr(c, s[cnt]) && !ft_strchr(o, s[cnt]) && (!s[cnt + 1] || ft_strchr(c, s[cnt + 1]) || ft_strchr(o, s[cnt + 1])))
				len += 1;
		}
		cnt += 1;
	}
	if (d_quote == IN_QUOTE || s_quote == IN_QUOTE)
		perror("quote error");
	return (len);
}

char	**lexer(char const *str)
{
	char	**lst;
	size_t	len;
	char	c[] = " \t\n\v\f\r";
	char	o[] = ";()<>|&";

	if (!str)
		return (NULL);
	len = count_word(str, c, o);
	lst = (char **)alloc_exit(sizeof(char *),  (len + 1));
	insert_word(lst, str, c, o);
	return (lst);
}
