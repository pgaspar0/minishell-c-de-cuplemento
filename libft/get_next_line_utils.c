/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 02:29:56 by pgaspar           #+#    #+#             */
/*   Updated: 2024/06/06 10:02:11 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *) s);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	return (0);
}

int	get_strlen(char	*s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
