/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:00 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:19:46 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_int_putchar(int n, int fd)
{
	char		res;

	res = '0' + n;
	write(fd, &res, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		result;
	int		remain;
	long	long_n;

	long_n = (long)n;
	if (long_n < 0)
	{
		write(fd, "-", 1);
		long_n = -long_n;
	}
	result = long_n / 10;
	remain = long_n % 10;
	if (long_n >= 10)
	{
		ft_putnbr_fd(result, fd);
	}
	ft_int_putchar(remain, fd);
}
