/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:58:13 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:09:48 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (size == 0 || nmemb == 0)
		p = (void *)malloc(sizeof(void) * 1);
	else if (nmemb > SIZE_T_MAX / size)
		return (NULL);
	else
		p = (void *) malloc (nmemb * size);
	if (p == NULL)
		return (NULL);
	if (size * nmemb != 0)
		ft_bzero(p, nmemb * size);
	else
		ft_bzero(p, 1);
	return (p);
}
