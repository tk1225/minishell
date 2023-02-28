/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:29:20 by atito             #+#    #+#             */
/*   Updated: 2022/10/14 11:33:31 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
		return (ft_putstr_fd("-2147483648", fd));
	else if (n < 0)
	{
		if (ft_putchar_fd('-', fd) == -1)
			return (-1);
		if (ft_putnbr_fd(-n, fd) == -1)
			return (-1);
	}
	else if (n >= 10)
	{
		if (ft_putnbr_fd(n / 10, fd) == -1)
			return (-1);
		if (ft_putchar_fd((n % 10) + '0', fd) == -1)
			return (-1);
	}
	else
	{
		if (ft_putchar_fd(n + '0', fd) == -1)
			return (-1);
	}
	return (0);
}
