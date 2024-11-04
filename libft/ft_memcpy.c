/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:22:14 by pgaspar           #+#    #+#             */
/*   Updated: 2024/05/15 18:11:53 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*c;
	const unsigned char	*d;

	c = (unsigned char *)dest;
	d = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		c[i] = d[i];
		i++;
	}
	return (dest);
}
