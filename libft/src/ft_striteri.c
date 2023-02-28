/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:53:07 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 13:02:09 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	cnt;

	if (!s || !f)
		return ;
	cnt = 0;
	while (s[cnt])
	{
		f(cnt, &s[cnt]);
		cnt += 1;
	}
}
