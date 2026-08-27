/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:16:41 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/22 10:31:34 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	new = malloc(sizeof(t_list) * 1);
	if (!new)
		return (NULL);
	current = new;
	while (lst)
	{
		current->content = f(lst->content);
		if (lst->next)
		{
			current->next = malloc(sizeof(t_list) * 1);
			if (!(current->next))
				return (ft_lstclear(&new, del), NULL);
		}
		else
			current->next = NULL;
		current = current->next;
		lst = lst->next;
	}
	return (new);
}
