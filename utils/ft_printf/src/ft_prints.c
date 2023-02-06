/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:58:51 by atito             #+#    #+#             */
/*   Updated: 2022/11/03 13:03:08 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	int	byte;

	byte = write(1, &c, 1);
	return (byte);
}

int	ft_print_str(char *str)
{
	int	byte;

	byte = 0;
	if (!str)
		byte = write(1, "(null)", 6);
	else
	{
		while (*str)
		{
			if (ft_print_char(*str++) == -1)
				return (-1);
			byte += 1;
		}
	}
	return (byte);
}

int	ft_print_pointer(uintptr_t dst)
{
	int		byte;
	int		len;
	char	*tmp;

	tmp = ft_ultoa(dst);
	if (!tmp)
		return (-1);
	len = 0;
	byte = ft_print_str("0x");
	if (byte == -1)
		return (-1);
	len += byte;
	byte = ft_print_str(tmp);
	free(tmp);
	if (byte == -1)
		return (-1);
	len += byte;
	return (len);
}
