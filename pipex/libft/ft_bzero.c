/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:09:15 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/15 08:53:41 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*auxiliar;

	auxiliar = (unsigned char *) s;
	while (n > 0)
	{
		*auxiliar = '\0';
		auxiliar++;
		n--;
	}
}
