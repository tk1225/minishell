/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:58:10 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:10:18 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t num)
{
	char	*target;

	target = (char *)str;
	while (num > 0)
	{
		*target = '\0';
		num --;
		target ++;
	}
	return ;
}
