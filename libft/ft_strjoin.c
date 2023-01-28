/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:17 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:26:57 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	size_t	tmp_cnt;
	size_t	s_cnt;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tmp)
		return (NULL);
	tmp_cnt = 0;
	s_cnt = 0;
	while (s1[s_cnt])
		tmp[tmp_cnt++] = s1[s_cnt++];
	s_cnt = 0;
	while (s2[s_cnt])
		tmp[tmp_cnt++] = s2[s_cnt++];
	tmp[tmp_cnt] = '\0';
	return (tmp);
}
