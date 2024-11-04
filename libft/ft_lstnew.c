/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:07:35 by pgaspar           #+#    #+#             */
/*   Updated: 2024/06/12 16:00:53 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*no;

	no = malloc(sizeof(t_list));
	if (!no)
		return (no = NULL);
	no -> content = content;
	no -> next = NULL;
	return (no);
}
