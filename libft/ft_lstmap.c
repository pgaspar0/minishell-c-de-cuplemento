/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:26:08 by pgaspar           #+#    #+#             */
/*   Updated: 2024/06/12 15:35:57 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlist;
	t_list	*save;

	if (!lst || !f || !del)
		return (NULL);
	nlist = ft_lstnew(f(lst -> content));
	if (!nlist)
		return (NULL);
	save = nlist;
	lst = lst -> next;
	while (lst)
	{
		nlist -> next = ft_lstnew(f(lst -> content));
		if (!nlist -> next)
		{
			ft_lstclear(&save, del);
			return (NULL);
		}
		nlist = nlist -> next;
		lst = lst -> next;
	}
	nlist -> next = NULL;
	return (save);
}
