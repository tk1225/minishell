/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:21 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:27:03 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	res;

	if (size == 0)
		return (ft_strlen(src));
	if (size < ft_strlen(dest) + 1)
	{
		res = size + ft_strlen(src);
		return (res);
	}
	else
		res = ft_strlen(src) + ft_strlen(dest);
	while (*dest != '\0' && size > 1)
	{
		dest ++;
		size --;
	}
	while (*src != '\0' && size > 1)
	{
		*dest = *src;
		src ++;
		dest ++;
		size --;
	}
	*dest = '\0';
	return (res);
}
