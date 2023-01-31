/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:09 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/31 16:24:11 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	un_ch;

	un_ch = (unsigned char)c;
	while (*s != '\0')
	{
		if (un_ch == *s)
			return ((char *)s);
		s ++;
	}
	// if (un_ch == *s)
	// 	return ((char *)s);
	return (0);
}
