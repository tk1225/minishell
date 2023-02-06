/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:49:28 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 13:03:24 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	cnt;
	size_t	s_len;
	char	*tmp;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		len = 0;
	else if (s_len - start < len)
		len = s_len - start;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	cnt = 0;
	while (s[start + cnt] && cnt < len)
	{
		tmp[cnt] = s[start + cnt];
		cnt += 1;
	}
	tmp[cnt] = '\0';
	return (tmp);
}
