/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:39 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:29:28 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*res;
	unsigned char	un_ch;

	un_ch = (unsigned char) c;
	res = 0;
	while (*s != '\0')
	{
		if (un_ch == *s)
			res = (char *)s;
		s ++;
	}
	if (un_ch == *s)
		res = (char *)s;
	return (res);
}
