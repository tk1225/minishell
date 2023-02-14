#include "minishell.h"

void	ft_expansion_dquote(char **com)
{
	char	*str;
	size_t	len;
	size_t	c_cnt;
	size_t	s_cnt;

	while (*com)
	{
		if (ft_strchr(*com ,'\"'))
		{
			len = 0;
			c_cnt = 0;
			while ((*com)[c_cnt])
			{
				if ((*com)[c_cnt] == '\"')
					len += 1;
				c_cnt += 1;
			}
			str = (char *)alloc_exit(sizeof(char), c_cnt - len + 1);
			s_cnt = 0;
			c_cnt = 0;
			while ((*com)[c_cnt])
			{
				while ((*com)[c_cnt] == '\"')
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

void	ft_expansion_squote(char **com)
{
	char	*str;
	size_t	len;
	size_t	c_cnt;
	size_t	s_cnt;

	while (*com)
	{
		if (ft_strchr(*com ,'\''))
		{
			len = 0;
			c_cnt = 0;
			while ((*com)[c_cnt])
			{
				if ((*com)[c_cnt] == '\'')
					len += 1;
				c_cnt += 1;
			}
			str = (char *)alloc_exit(sizeof(char), c_cnt - len + 1);
			s_cnt = 0;
			c_cnt = 0;
			while ((*com)[c_cnt])
			{
				while ((*com)[c_cnt] == '\'')
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
	char	*tmp1;
	char	*tmp2;
	size_t	cnt;
	size_t	len;

	while (*com)
	{
		cnt = 0;
		while((*com)[cnt])
		{
			if ((*com)[cnt++] == '$' && !(ft_strchr(*com, '\'')))
			{
				len = 0;
				while ((*com)[cnt] != '$' && (*com)[cnt] && !ft_strchr(" \t\n\v\f\r", (*com)[cnt]))
				{
					cnt += 1;
					len += 1;
				}
				tmp1 = ft_substr(*com, cnt - len, len);
				if (tmp1[0] == '\0')
				{
					str = alloc_exit(sizeof(char), 2);
					str[0] = '$';
					str[1] = '\0';
				}
				else if (tmp1[0] == '?')
				{
					str = ft_strdup(tmp1);
					str[0] = '0';
				}
				else
					str = getenv(tmp1);
				free(tmp1);
				tmp1 = ft_substr(*com, 0, cnt - len - 1);
				tmp2 = ft_substr(*com, cnt, ft_strlen(*com) - cnt);
				free(*com);
				*com = str_join_three(tmp1, str, tmp2);
				free(tmp1);
				free(tmp2);
				cnt += ft_strlen(str) - len - 1;
			}
		}
		com += 1;
	}
}
