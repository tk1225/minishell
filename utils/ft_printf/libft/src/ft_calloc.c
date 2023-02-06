/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:53:06 by atito             #+#    #+#             */
/*   Updated: 2022/10/21 12:39:35 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t cnt, size_t size)
{
	void	*tmp;

	if (cnt == 0 || size == 0)
		tmp = (void *)malloc(sizeof(void) * 1);
	else if (cnt > SIZE_T_MAX / size)
		return (NULL);
	else
		tmp = (void *)malloc(sizeof(void) * size * cnt);
	if (!tmp)
		return (NULL);
	if (cnt * size != 0)
		ft_bzero(tmp, size * cnt);
	else
		ft_bzero(tmp, 1);
	return (tmp);
}
