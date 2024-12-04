/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:45:39 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/17 14:20:02 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*aux_s1;
	const unsigned char	*aux_s2;
	size_t				i;

	i = 0;
	aux_s1 = (const unsigned char *)s1;
	aux_s2 = (const unsigned char *)s2;
	while (i != n)
	{
		if (aux_s1[i] != aux_s2[i])
			return (aux_s1[i] - aux_s2[i]);
		i++;
	}
	return (0);
}
