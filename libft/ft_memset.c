/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:58:50 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:19:18 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *target_input, int insert, size_t num)
{
	unsigned char	*target;
	unsigned char	for_insert;

	for_insert = (unsigned char)insert;
	target = (unsigned char *)target_input;
	while (num > 0)
	{
		*target = for_insert;
		num --;
		target ++;
	}
	return (target_input);
}
