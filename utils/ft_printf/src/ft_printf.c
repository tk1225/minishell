/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:26:53 by atito             #+#    #+#             */
/*   Updated: 2022/11/03 13:15:15 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_free_null(char *str)
{
	int	byte;

	byte = ft_print_str(str);
	free(str);
	str = NULL;
	return (byte);
}

int	next_check(char str, va_list *arg)
{
	int		byte;

	byte = 0;
	if (str == 'c')
		byte = ft_print_char(va_arg(*arg, int));
	else if (str == 's')
		byte = ft_print_str(va_arg(*arg, char *));
	else if (str == 'p')
		byte = ft_print_pointer(va_arg(*arg, uintptr_t));
	else if (str == 'd' || str == 'i')
		byte = print_free_null(ft_itoa(va_arg(*arg, int)));
	else if (str == 'u')
		byte = print_free_null(ft_uitoa(va_arg(*arg, unsigned int)));
	else if (str == 'x')
		byte = print_free_null(hex_num(va_arg(*arg, unsigned int)));
	else if (str == 'X')
		byte = print_free_null(str_upper(hex_num(va_arg(*arg, unsigned int))));
	else if (str == '%')
		byte = ft_print_char('%');
	return (byte);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	size_t	cnt;
	int		byte;
	int		len;

	cnt = 0;
	byte = 0;
	len = 0;
	va_start(arg, format);
	while (format[cnt])
	{
		if (format[cnt] == '%')
			byte = next_check(format[++cnt], &arg);
		else
			byte = write(1, &format[cnt], 1);
		if (byte == -1)
			return (0);
		cnt += 1;
		len += byte;
	}
	va_end(arg);
	return (len);
}
