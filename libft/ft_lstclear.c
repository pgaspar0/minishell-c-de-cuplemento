/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:04:37 by pgaspar           #+#    #+#             */
/*   Updated: 2024/06/12 16:14:17 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;
	t_list	*tp;

	t = *lst;
	while (t)
	{
		tp = t -> next;
		ft_lstdelone(t, del);
		t = tp;
	}
	*lst = NULL;
}
