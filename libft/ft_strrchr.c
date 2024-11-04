/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:14:20 by nmendes           #+#    #+#             */
/*   Updated: 2024/05/18 20:03:40 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_pos;

	last_pos = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last_pos = (char *)s;
		++s;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (last_pos);
}
