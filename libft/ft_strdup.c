/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:12 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:25:35 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;

	res = (char *)malloc(ft_strlen(s) + 1);
	if (NULL == res)
		return (NULL);
	if ((s != NULL) && (ft_strlen(s) == 0))
	{
		res[0] = '\0';
		return (res);
	}
	ft_strlcpy(res, s, ft_strlen(s) + 1);
	return (res);
}
