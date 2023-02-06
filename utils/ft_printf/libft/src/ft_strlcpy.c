/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:56:22 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 12:43:53 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	cnt;

	cnt = 0;
	if (dstsize)
	{
		while (src[cnt] && cnt < (dstsize - 1))
		{
			dst[cnt] = src[cnt];
			cnt += 1;
		}
		dst[cnt] = '\0';
	}
	return (ft_strlen(src));
}
