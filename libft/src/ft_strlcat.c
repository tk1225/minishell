/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:02:16 by atito             #+#    #+#             */
/*   Updated: 2022/10/16 17:38:28 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	cnt;
	size_t	dst_len;

	if (!dst && src && dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	if (dstsize < dst_len)
		return (ft_strlen(src) + dstsize);
	cnt = 0;
	while (dst_len + cnt + 1 < dstsize && src[cnt])
	{
		dst[dst_len + cnt] = src[cnt];
		cnt += 1;
	}
	dst[dst_len + cnt] = '\0';
	return (dst_len + ft_strlen(src));
}
