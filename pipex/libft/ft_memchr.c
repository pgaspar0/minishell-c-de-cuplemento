/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:37:12 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/17 13:39:36 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t	n)
{
	unsigned char	*auxiliar;

	auxiliar = (unsigned char *)s;
	while (n--)
	{
		if (*auxiliar == (unsigned char)c)
			return (auxiliar);
		auxiliar++;
	}
	return (NULL);
}
