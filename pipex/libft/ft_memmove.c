/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:36:08 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/15 16:44:05 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*aux_dest;
	const char	*aux_src;
	size_t		i;

	aux_dest = (char *)dest;
	aux_src = (const char *)src;
	i = 0;
	if (aux_dest < aux_src)
	{
		while (i < n)
		{
			aux_dest[i] = aux_src[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			aux_dest[i] = aux_src[i];
		}
	}
	return (dest);
}
