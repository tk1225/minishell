/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:26:09 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 13:03:00 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_check(char c, char const *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
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
