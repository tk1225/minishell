/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:41 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:29:52 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_check(char c, char const *set)
{
	size_t	cnt;

	cnt = 0;
	while (set[cnt])
	{
		if (set[cnt] == c)
			return (1);
		cnt += 1;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	cnt;
	char	*tmp;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (set_check(s1[start], set) && s1[start])
		start += 1;
	end = ft_strlen(s1);
	while (set_check(s1[end - 1], set) && start < end)
		end -= 1;
	tmp = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!tmp)
		return (NULL);
	cnt = 0;
	while (start < end)
		tmp[cnt++] = s1[start++];
	tmp[cnt] = '\0';
	return (tmp);
}
