/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:57:20 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:17:04 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = (t_list *)malloc(sizeof(t_list));
	if (res == NULL)
	{
		return (NULL);
	}
	res->content = content;
	res->next = NULL;
	return (res);
}
