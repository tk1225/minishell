/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:02:01 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 16:01:22 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	insert_num(char *str, int n, int len)
{
	long	tmp;

	tmp = n;
	if (n < 0)
	{
		tmp *= -1;
		*str = '-';
	}
	str += len;
	*str-- = '\0';
	if (tmp == 0)
		*str = '0';
	while (tmp > 0)
	{
		*str-- = (tmp % 10) + '0';
		tmp /= 10;
	}
}

char	*ft_itoa(int n)
{
	long	tmp;
	int		len;
	char	*num_str;

	tmp = n;
	len = 0;
	if (n < 0)
	{
		tmp *= -1;
		len += 1;
	}
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
	insert_num(num_str, n, len);
	return (num_str);
}
