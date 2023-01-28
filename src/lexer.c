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

	cnt = 0;
	len = 0;
	while (s[cnt])
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
		cnt += 1;
	}
	*lst = NULL;
}

char	**lexer(char const *s, char *c)
{
	char	**lst;
	size_t	cnt;
	int		len;

	if (!s)
		return (NULL);
	cnt = 0;
	len = 0;
	while (s[cnt])
	{
		if (!ft_strchr(c, s[cnt]) && (ft_strchr(c, s[cnt + 1]) || !s[cnt + 1]))
			len += 1;
		cnt += 1;
	}
	lst = (char **)malloc(sizeof(char *) * (len + 1));
	if (!lst)
		return (NULL);
	insert_word(s, c, lst);
	return (lst);
}
