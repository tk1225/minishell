/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:44 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:29:59 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*resstr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (ft_strlen(s) > len)
		resstr = (char *)malloc(len + 1);
	else
		resstr = (char *)malloc(ft_strlen(s) + 1);
	if (NULL == resstr)
		return (NULL);
	while (s[start] != '\0' && i < len && start <= ft_strlen(s))
	{
		resstr[i] = s[start];
		start ++;
		i ++;
	}
	resstr[i] = '\0';
	return (&resstr[0]);
}
