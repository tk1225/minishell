/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:36 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:29:13 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	strloc;
	size_t	j;

	if ((to_find != NULL && len == 0 && str == NULL) || \
	(to_find[0] == 0 && str != NULL))
		return ((char *)str);
	strloc = 0;
	while ((str[strloc] != 0) && (len > 0))
	{
		if (str[strloc] == to_find[0])
		{
			j = 0;
			while (to_find[j] != 0 && ((len - j) > 0))
			{
				if (str[strloc + j] != to_find[j])
					break ;
				j++;
			}
			if (j == ft_strlen(to_find))
				return ((char *)&str[strloc]);
		}
		strloc++;
		len --;
	}
	return (NULL);
}
