/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:33 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:28:47 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*un_s1;
	unsigned char	*un_s2;

	un_s1 = (unsigned char *)s1;
	un_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (un_s1[i] != '\0' && un_s2[i] != '\0' && i < n)
	{
		if (un_s1[i] != un_s2[i])
			return (un_s1[i] - un_s2[i]);
		i++;
	}
	if (i != n)
		return (un_s1[i] - un_s2[i]);
	return (0);
}
