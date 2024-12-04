/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:22:18 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/21 13:34:46 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_toklen(const char *s, char c)
{
	size_t	ret;
	size_t	i;

	ret = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			++ret;
			while (s[i] && s[i] != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	len;

	if (s == 0)
		return (0);
	i = 0;
	ptr = malloc(sizeof(char *) * (ft_toklen(s, c) + 1));
	if (ptr == 0)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			ptr[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	ptr[i] = 0;
	return (ptr);
}
