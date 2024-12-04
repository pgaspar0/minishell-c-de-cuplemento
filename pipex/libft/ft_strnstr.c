/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:08:13 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/17 18:22:31 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_strnstr(const char *aux_s1, const char *aux_s2, size_t len)
{
	char	*hay;
	size_t	i;
	size_t	c;
	size_t	n_len;

	i = 0;
	hay = (char *)aux_s1;
	n_len = ft_strlen(aux_s2);
	if (n_len == 0 || aux_s1 == aux_s2)
		return (hay);
	while (hay[i] != '\0' && i < len)
	{
		c = 0;
		while (hay[i + c] != '\0' && aux_s2[c] != '\0' && hay[i
				+ c] == aux_s2[c] && i + c < len)
			c++;
		if (c == n_len)
			return (hay + i);
		i++;
	}
	return (0);
}
