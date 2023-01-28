/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:57:20 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 11:16:39 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new_node;

	if (lst == NULL || f == NULL || del == NULL)
		return (lst);
	else
	{
		head = NULL;
		while (lst != NULL)
		{
			new_node = ft_lstnew(f(lst->content));
			if (new_node == NULL)
			{
				ft_lstclear(&head, del);
				return (NULL);
			}
			ft_lstadd_back(&head, new_node);
			lst = lst->next;
		}
	}
	return (head);
}
