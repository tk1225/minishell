/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:58:19 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 12:42:00 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*tmp_dst;
	const unsigned char	*tmp_src;

	tmp_dst = (unsigned char *)dst;
	tmp_src = (const unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst <= src)
	{
		while (n--)
			*tmp_dst++ = *tmp_src++;
	}
	else
	{
		tmp_dst += n;
		tmp_src += n;
		while (n--)
			*--tmp_dst = *--tmp_src;
	}
	return (dst);
}
