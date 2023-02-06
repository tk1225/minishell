/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:47:57 by atito             #+#    #+#             */
/*   Updated: 2022/10/29 15:54:26 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	insert_num(char *str, unsigned int n, int len)
{
	str += len;
	*str-- = '\0';
	if (n == 0)
		*str = '0';
	while (n > 0)
	{
		if (n % 16 < 10)
			*str-- = (n % 16) + '0';
		else
			*str-- = (n % 16) + 'a' - 10;
		n /= 16;
	}
}

char	*hex_num(unsigned int n)
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
		tmp /= 16;
		len += 1;
	}
	num_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!num_str)
		return (NULL);
	insert_num(num_str, n, len);
	return (num_str);
}

static void	insert_ulnum(char *str, uintptr_t n, int len)
{
	str += len;
	*str-- = '\0';
	if (n == 0)
		*str = '0';
	while (n > 0)
	{
		if (n % 16 < 10)
			*str-- = (n % 16) + '0';
		else
			*str-- = (n % 16) + 'a' - 10;
		n /= 16;
	}
}

char	*ft_ultoa(uintptr_t n)
{
	uintptr_t	tmp;
	int			len;
	char		*num_str;

	tmp = n;
	len = 0;
	if (tmp == 0)
		len += 1;
	while (tmp > 0)
	{
		tmp /= 16;
		len += 1;
	}
	num_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!num_str)
		return (NULL);
	insert_ulnum(num_str, n, len);
	return (num_str);
}
