/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_upper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:44:11 by atito             #+#    #+#             */
/*   Updated: 2022/10/22 19:00:08 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*str_upper(char *str)
{
	size_t	cnt;

	if (!str)
		return (NULL);
	cnt = 0;
	while (str[cnt])
	{
		str[cnt] = (char)ft_toupper(str[cnt]);
		cnt += 1;
	}
	return (str);
}
