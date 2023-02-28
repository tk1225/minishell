/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:33:25 by atito             #+#    #+#             */
/*   Updated: 2022/10/16 16:51:14 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				cnt;
	const unsigned char	*tmp_s1;
	const unsigned char	*tmp_s2;

	tmp_s1 = (const unsigned char *)s1;
	tmp_s2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	cnt = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return ((int)-tmp_s2[cnt]);
	if (!s2)
		return ((int)tmp_s1[cnt]);
	while ((tmp_s1[cnt] || tmp_s2[cnt]) && cnt < n)
	{
		if (tmp_s1[cnt] != tmp_s2[cnt])
			return ((int)(tmp_s1[cnt] - tmp_s2[cnt]));
		cnt += 1;
	}
	return (0);
}
