#include "minishell.h"

void	ft_expansion_quote(char **com)
{
	char	*str;
	size_t	len;
	size_t	c_cnt;
	size_t	s_cnt;

	while (*com)
	{
		if (ft_strchr(*com, '\'') || ft_strchr(*com, '\"'))
		{
			len = 0;
			c_cnt = 0;
			while ((*com)[c_cnt])
			{
				if ((*com)[c_cnt] == '\'' || (*com)[c_cnt] == '\"')
					len += 1;
				c_cnt += 1;
			}
			str = (char *)alloc_exit(sizeof(char), c_cnt - len + 1);
			s_cnt = 0;
			c_cnt = 0;
			while ((*com)[c_cnt])
			{
				while ((*com)[c_cnt] == '\'' || (*com)[c_cnt] == '\"')
					c_cnt += 1;
				str[s_cnt++] = (*com)[c_cnt++];
			}
			str[c_cnt] = '\0';
			free(*com);
			*com = str;
		}
		com += 1;
	}
}

void	ft_expansion_env(char **com)
{
	char	*str;

	while (*com)
	{
		if ((*com)[0] == '$')
		{
			str = getenv(&(*com)[1]);
			if (!str)
				str = ft_calloc(1, 1);
			free(*com);
			*com = str;
		}
		com += 1;
	}
}

//echo "aa"
