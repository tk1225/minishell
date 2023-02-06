/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:50:01 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 13:02:29 by atito            ###   ########.fr       */
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
	s_cnt = 0;
	tmp_cnt = 0;
	while (s1[s_cnt])
		tmp[tmp_cnt++] = s1[s_cnt++];
	s_cnt = 0;
	while (s2[s_cnt])
		tmp[tmp_cnt++] = s2[s_cnt++];
	tmp[tmp_cnt] = '\0';
	return (tmp);
}
