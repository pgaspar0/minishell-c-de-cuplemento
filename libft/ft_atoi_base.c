/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:40:31 by pgaspar           #+#    #+#             */
/*   Updated: 2024/08/23 11:46:30 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *str, int str_base)
{
	int	i;
	int	sinal;

	i = 0;
	sinal = 1;
	if (str[0] == '-')
	{
		sinal = -1;
		str++;
	}
	else if ((str[0] == '+') || (str[0] == '-'))
		str++;
	while (*str && ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F')
			|| (*str >= 'a' && *str <= 'f')))
	{
		if (*str >= 'A' && *str <= 'F')
			i = (i * str_base + (*str++ - 'A' + 10));
		else if (*str >= 'a' && *str <= 'f')
			i = (i * str_base + (*str++ - 'a' + 10));
		else
			i = (i * str_base + (*str++ - '0'));
	}
	return (i * sinal);
}
