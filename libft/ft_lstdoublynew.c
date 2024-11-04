/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdoublynew.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:07:35 by pgaspar           #+#    #+#             */
/*   Updated: 2024/06/26 12:23:03 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

node	*ft_lstdoublynew(int value)
{
	node	*no;

	no = malloc(sizeof(node));
	if (!no)
		return (0);
	no->value = value;
	no->prev = NULL;
	no->next = NULL;
	return (no);
}
