/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:58:44 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:18:23 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest_input, const void *src_input, size_t num)
{
	unsigned char	*dest;
	unsigned char	*src;

	if (dest_input == NULL && src_input == NULL)
		return (NULL);
	dest = (unsigned char *)dest_input;
	src = (unsigned char *)src_input;
	while (num > 0)
	{
		*dest = *src;
		src ++;
		dest ++;
		num --;
	}
	return (dest_input);
}
