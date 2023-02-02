#include "minishell.h"

void	free_lst(char **lst)
{
	while (*lst)
		free (*lst++);
	free (lst);
}

static void	insert_word(char **lst, char const *s, char *c, char *o)
{
	size_t	cnt;
	size_t	len;
	int		s_quote;
	int		d_quote;

	cnt = 0;
	len = 0;
	s_quote = 1;
	d_quote = 1;
	while (s[cnt])
	{
		if (s[cnt] == '\"')
			d_quote *= -1;
		if (s[cnt] == '\'')
			s_quote *= -1;
		if (!(ft_strchr(c, s[cnt]) && d_quote == 1 && s_quote == 1))
			len += 1;
		if (d_quote == 1 && s_quote == 1 && !ft_strchr("\'\"", s[cnt + 1]))
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
	s_quote = 1;
	d_quote = 1;
	while (s[cnt])
	{
		if (s[cnt] == '\"')
			d_quote *= -1;
		if (s[cnt] == '\'')
			s_quote *= -1;
		if (d_quote == 1 && s_quote == 1 && !ft_strchr("\'\"", s[cnt + 1]))
		{
			if (!ft_strchr(c, s[cnt]) && !ft_strchr(o, s[cnt]) && (!s[cnt + 1] || ft_strchr(c, s[cnt + 1]) || ft_strchr(o, s[cnt + 1])))
				len += 1;
			if (ft_strchr(o, s[cnt]) && !ft_strchr(o, s[cnt + 1]))
				len += 1;
		}
		cnt += 1;
	}
	return (len);
}

char	**lexer(char const *s)
{
	char	**lst;
	size_t	len;
	char	c[] = " \t\n\v\f\r";
	char	o[] = ";()<>|&";

	if (!s)
		return (NULL);
	len = count_word(s, c, o);
	lst = (char **)alloc_exit(sizeof(char *),  (len + 1));
	insert_word(lst, s, c, o);
	return (lst);
}
