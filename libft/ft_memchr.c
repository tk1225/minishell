/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:58:38 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:17:47 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *target, int ch, size_t n)
{
	unsigned char			*tmp;
	unsigned char			un_ch;

	tmp = (unsigned char *)target;
	un_ch = (unsigned char) ch;
	while (n > 0)
	{
		if (*tmp == un_ch)
			return (tmp);
		tmp ++;
		n --;
	}
	return (0);
}
