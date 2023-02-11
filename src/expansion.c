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
	char	*tmp1;
	char	*tmp2;
	size_t	cnt;
	size_t	len;

	while (*com)
	{
		cnt = 0;
		while((*com)[cnt])
		{
			if ((*com)[cnt++] == '$')
			{
				len = 0;
				while ((*com)[cnt] != '$' && (*com)[cnt])
				{
					cnt += 1;
					len += 1;
				}
				tmp1 = ft_substr(*com, cnt - len, len);
				str = getenv(tmp1);
				free(tmp1);
				tmp1 = ft_substr(*com, 0, cnt - len - 1);
				tmp2 = ft_substr(*com, cnt, ft_strlen(*com) - cnt);
				free(*com);
				*com = str_join_three(tmp1, str, tmp2);
				free(tmp1);
				free(tmp2);
				cnt = 0;
			}
		}
		com += 1;
	}
}

//echo "aa"
//echo $USER
//echo $USER$USER
