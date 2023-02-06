/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:44:43 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 12:41:35 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*tmp_s;

	tmp_s = (const unsigned char *)s;
	while (n--)
	{
		if (*tmp_s == (unsigned char)c)
			return ((void *)tmp_s);
		tmp_s += 1;
	}
	return (NULL);
}
