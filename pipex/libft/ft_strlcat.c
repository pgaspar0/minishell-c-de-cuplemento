/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:10:21 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/16 08:54:00 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	hold;
	size_t	str_len;

	str_len = ft_strlen(src);
	dst_len = 0;
	while (dst_len < size && dst[dst_len])
		dst_len++;
	hold = dst_len;
	while (src[dst_len - hold] && (dst_len + 1) < size)
	{
		dst[dst_len] = src[dst_len - hold];
		dst_len++;
	}
	if (hold < size)
		dst[dst_len] = '\0';
	return (hold + str_len);
}
