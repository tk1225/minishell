#include "minishell.h"

static void	free_lst(char **lst)
{
	while (*lst)
		free (*lst++);
	free (lst);
}

static void	insert_word(char const *s, char *c, char **lst)
{
	int	cnt;
	int	len;
    int quote_single;
    int quote_double;
    char quote;

	cnt = 0;
	len = 0;
    quote_single = OUT_QUOTE;
    quote_double = OUT_QUOTE;
	while (s[cnt])
	{
        if (s[cnt] == '\"')
        {
            quote_double *= -1;
            cnt++;
        }
        if (s[cnt] == '\'')
        {
            quote_single *= -1;
            cnt++;
        }
        if ((quote_double == OUT_QUOTE) && (quote_single == OUT_QUOTE))
        {
            if (!ft_strchr(c, s[cnt]))
			    len += 1;
		    if (!ft_strchr(c, s[cnt]) && (ft_strchr(c, s[cnt + 1]) || !s[cnt + 1]))
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
        else
        {
            if (quote_double == IN_QUOTE)
                quote = '\"';
            else if (quote_single == IN_QUOTE)
                quote = '\'';
            if (s[cnt] != quote)
			    len += 1; 
		    if (s[cnt + 1] == quote)
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

char	**lexer(char const *s, char *c)
{
	char	**lst;
	size_t	cnt;
	int		len;
    int     quote_single;
    int     quote_double;

	if (!s)
		return (NULL);
	cnt = 0;
	len = 0;
    quote_single = OUT_QUOTE;
    quote_double = OUT_QUOTE;

	while (s[cnt])
	{
        if (s[cnt] == '\"')
            quote_double *= -1;
        if (s[cnt] == '\'')
            quote_single *= -1;
        //quote内であれば区切り文字であっても飛ばすように変更
        if ((quote_double == OUT_QUOTE) && (quote_single == OUT_QUOTE))
        {
            if (!ft_strchr(c, s[cnt]) && (ft_strchr(c, s[cnt + 1]) || !s[cnt + 1]))
			    len += 1;
        }
		cnt += 1;
	}
	lst = (char **)malloc(sizeof(char *) * (len + 1));
	if (!lst)
		return (NULL);
	insert_word(s, c, lst);
	return (lst);
}
