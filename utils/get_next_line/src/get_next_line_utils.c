/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 09:29:37 by atito             #+#    #+#             */
/*   Updated: 2022/11/01 19:18:40 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len += 1;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s += 1;
	}
	if (!c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	size_t	tmp_cnt;
	size_t	s_cnt;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	tmp_cnt = 0;
	s_cnt = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tmp)
		return (NULL);
	while (s1[s_cnt])
		tmp[tmp_cnt++] = s1[s_cnt++];
	s_cnt = 0;
	while (s2[s_cnt])
		tmp[tmp_cnt++] = s2[s_cnt++];
	tmp[tmp_cnt] = '\0';
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	cnt;
	char	*tmp;

	cnt = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	while (s[start + cnt] && cnt < len)
	{
		tmp[cnt] = s[start + cnt];
		cnt += 1;
	}
	tmp[cnt] = '\0';
	return (tmp);
}

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	cnt;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!tmp)
		return (NULL);
	cnt = 0;
	while (s1[cnt])
	{
		tmp[cnt] = s1[cnt];
		cnt += 1;
	}
	tmp[cnt] = '\0';
	return (tmp);
}
