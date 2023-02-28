/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:14:56 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 12:53:30 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	long_check(unsigned long num, const char c, int np)
{
	unsigned long	long_div;
	unsigned long	long_mod;

	long_div = LONG_MAX / 10;
	long_mod = LONG_MAX % 10;
	if (num > long_div && c)
		return (np);
	if (num == long_div && (unsigned long)(c - '0') > long_mod && np == 1)
		return (1);
	if (num == long_div && (unsigned long)(c - '0') > long_mod + 1 && np == -1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t			cnt;
	unsigned long	num;
	int				np;

	cnt = 0;
	while ((str[cnt] >= '\t' && str[cnt] <= '\r') || str[cnt] == ' ')
		cnt += 1;
	np = 1;
	if (str[cnt] == '+' || str[cnt] == '-')
	{
		if (str[cnt] == '-')
			np = -1;
		cnt += 1;
	}
	num = 0;
	while (str[cnt] >= '0' && str[cnt] <= '9')
	{
		num = num * 10 + (str[cnt] - '0');
		cnt += 1;
		if (long_check(num, str[cnt], np) == 1)
			return ((int)LONG_MAX);
		if (long_check(num, str[cnt], np) == -1)
			return ((int)LONG_MIN);
	}
	return ((int)(num * np));
}
