/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:58:47 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:18:49 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest_input, const void *src_input, size_t num)
{
	unsigned char		*dest;
	const unsigned char	*src;

	if (dest_input == NULL && src_input == NULL)
		return (NULL);
	dest = (unsigned char *)dest_input;
	src = (const unsigned char *)src_input;
	if (dest > src)
	{
		dest += num - 1;
		src += num - 1;
		while (num --)
			*dest-- = *src--;
	}
	else
	{
		while (num --)
			*dest++ = *src++;
	}
	return (dest_input);
}
