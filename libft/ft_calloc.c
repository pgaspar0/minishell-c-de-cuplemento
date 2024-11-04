/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:04:17 by pgaspar           #+#    #+#             */
/*   Updated: 2024/05/18 19:30:43 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ar;
	size_t	size_max;

	size_max = 4294967295;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (nmemb > size_max / size)
		return (NULL);
	ar = malloc(nmemb * size);
	if (!ar)
		return (NULL);
	ft_bzero(ar, nmemb * size);
	return (ar);
}
