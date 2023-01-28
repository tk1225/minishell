/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:58:33 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:10:43 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_num_size(long n)
{
	int	res;

	res = 1;
	if (n < 0)
	{
		n = -n;
		res ++;
	}
	while (n >= 10)
	{
		n /= 10;
		res ++;
	}
	return (res);
}

static char	*ft_itoa_helper(long long_n, char *res)
{
	if (long_n < 0)
	{
		long_n = -long_n;
		*res = '-';
		res ++;
	}
	res += ft_check_num_size(long_n);
	*res = '\0';
	res --;
	while (long_n >= 10)
	{
		*res = long_n % 10 + '0';
		long_n /= 10;
		res --;
	}
	*res = long_n + '0';
	return (res);
}

char	*ft_itoa(int n)
{
	char			*res;
	char			*tmp;
	long			long_n;

	long_n = n;
	res = (char *) malloc (ft_check_num_size(long_n) + 1);
	if (res == NULL)
		return (NULL);
	tmp = res;
	ft_itoa_helper(long_n, res);
	return (tmp);
}
