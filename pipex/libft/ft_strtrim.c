/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:07:40 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/20 18:22:24 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	ptr = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		len = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[len - 1] && ft_strchr(set, s1[len - 1]) && len > i)
			len--;
		ptr = (char *)malloc(sizeof(char) * (len - i + 1));
		if (ptr)
			ft_strlcpy(ptr, &s1[i], len - i + 1);
	}
	return (ptr);
}
