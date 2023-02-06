/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:40:05 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 12:45:11 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	cnt;
	size_t	s2_len;

	s2_len = ft_strlen(s2);
	if (s2_len == 0)
		return ((char *)s1);
	if (n == 0)
		return (NULL);
	cnt = 0;
	while (s1[cnt] && cnt + s2_len <= n)
	{
		if (!ft_strncmp(&s1[cnt], s2, s2_len))
			return ((char *)&s1[cnt]);
		cnt += 1;
	}
	return (NULL);
}
