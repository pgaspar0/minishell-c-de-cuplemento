/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:34:13 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/20 13:02:47 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(dst);
	while (src[i] != '\0')
	{
		dst[length + i] = src[i];
		i++;
	}
	dst[length + i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	joined_str = (char *)malloc(sizeof(char) * (size + 1));
	if (joined_str == NULL)
		return (NULL);
	joined_str[0] = '\0';
	ft_strcat(joined_str, s1);
	ft_strcat(joined_str, s2);
	return (joined_str);
}
