/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:43:03 by atito             #+#    #+#             */
/*   Updated: 2022/10/22 19:00:11 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	insert_unum(char *str, unsigned int n, int len)
{
	str += len;
	*str-- = '\0';
	if (n == 0)
		*str = '0';
	while (n > 0)
	{
		*str-- = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_uitoa(unsigned int n)
{
	unsigned int	tmp;
	int				len;
	char			*num_str;

	tmp = n;
	len = 0;
	if (tmp == 0)
		len += 1;
	while (tmp > 0)
	{
		tmp /= 10;
		len += 1;
	}
	num_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!num_str)
		return (NULL);
	insert_unum(num_str, n, len);
	return (num_str);
}
