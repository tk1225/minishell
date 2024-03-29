/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:23:57 by atito             #+#    #+#             */
/*   Updated: 2023/03/18 13:20:28 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	expansion_char(char **str, char *com, size_t cnt)
{
	char	*tmp;
	size_t	s_cnt;
	size_t	len;

	len = ft_strlen(*str);
	tmp = (char *)alloc_exit(sizeof(char), len + 2);
	s_cnt = 0;
	while (s_cnt < len)
	{
		tmp[s_cnt] = (*str)[s_cnt];
		s_cnt += 1;
	}
	tmp[s_cnt++] = com[cnt++];
	tmp[s_cnt] = '\0';
	free(*str);
	*str = tmp;
	return (cnt);
}

size_t	expansion_env(t_env **env, char **str, char *com, size_t cnt)
{
	size_t		len;
	char		*prm;
	char		*tmp;

	len = 0;
	while (ft_isalnum(com[cnt]) || com[cnt] == '_')
	{
		cnt += 1;
		len += 1;
		if (ft_isdigit(com[1]))
			break ;
	}
	prm = ft_substr(com, cnt - len, len);
	tmp = next_dollar(env, str, prm);
	free(prm);
	free(*str);
	*str = tmp;
	return (cnt);
}

static size_t	expansion_dquote(t_env **env, char **str, char *com, size_t cnt)
{
	char	*inq;
	char	*tmp;

	inq = NULL;
	while (com[cnt] != '\"')
	{
		if (com[cnt] == '$')
			cnt = expansion_env(env, &inq, com, cnt + 1);
		else
			cnt = expansion_char(&inq, com, cnt);
	}
	tmp = ft_strjoin(*str, inq);
	free(*str);
	free(inq);
	*str = tmp;
	return (cnt + 1);
}

static size_t	expansion_squote(char **str, char *com, size_t cnt)
{
	char	*inq;
	char	*tmp;

	inq = NULL;
	while (com[cnt] != '\'')
		cnt = expansion_char(&inq, com, cnt);
	tmp = ft_strjoin(*str, inq);
	free(*str);
	free(inq);
	*str = tmp;
	return (cnt + 1);
}

void	expansion(char **com, t_env **env)
{
	char	*str;
	size_t	c_cnt;

	while (*com)
	{
		c_cnt = 0;
		str = NULL;
		while ((*com)[c_cnt])
		{
			if ((*com)[c_cnt] == '$')
				c_cnt = expansion_env(env, &str, *com, c_cnt + 1);
			else if ((*com)[c_cnt] == '\"')
				c_cnt = expansion_dquote(env, &str, *com, c_cnt + 1);
			else if ((*com)[c_cnt] == '\'')
				c_cnt = expansion_squote(&str, *com, c_cnt + 1);
			else
				c_cnt = expansion_char(&str, *com, c_cnt);
		}
		free(*com);
		if (!str)
			str = ft_calloc(sizeof(char), 1);
		*com = str;
		com += 1;
	}
}
