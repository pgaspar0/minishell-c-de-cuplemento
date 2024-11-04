/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hfuncs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:54:57 by pgaspar           #+#    #+#             */
/*   Updated: 2024/05/26 13:13:58 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	int_to_hex_upper(unsigned int i, int *c)
{
	if (i >= 16)
		int_to_hex_upper(i / 16, c);
	ft_putchar("0123456789ABCDEF"[i % 16], c);
}

void	int_to_hex_lower(unsigned int i, int *c)
{
	if (i >= 16)
		int_to_hex_lower(i / 16, c);
	ft_putchar("0123456789abcdef"[i % 16], c);
}

static void	int_to_hex(unsigned long long i, int *c)
{
	if (i >= 16)
		int_to_hex(i / 16, c);
	ft_putchar("0123456789abcdef"[i % 16], c);
}

void	print_pointer(void *p, int *c)
{
	if (!p)
		ft_putstr("(nil)", c);
	else
	{
		ft_putstr("0x", c);
		int_to_hex((unsigned long long)p, c);
	}
}
