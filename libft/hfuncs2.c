/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hfuncs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:04:32 by pgaspar           #+#    #+#             */
/*   Updated: 2024/05/26 13:13:11 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int *i)
{
	write(1, &c, 1);
	(*i)++;
}

void	ft_unsigned(unsigned int n, int *c)
{
	if (n > 9)
	{
		ft_unsigned(n / 10, c);
		ft_unsigned(n % 10, c);
	}
	else
		ft_putchar(n + 48, c);
}

void	ft_putstr(char *str, int *c)
{
	if (!str)
		ft_putstr("(null)", c);
	else
	{
		while (*str)
		{
			ft_putchar(*str++, c);
		}
	}
}

void	ft_putnbr(int nb, int *i)
{
	if (nb == -2147483648)
	{
		ft_putchar('-', i);
		ft_putchar('2', i);
		ft_putnbr(147483648, i);
	}
	else if (nb < 0)
	{
		ft_putchar('-', i);
		nb = -nb;
		ft_putnbr(nb, i);
	}
	else if (nb > 9)
	{
		ft_putnbr(nb / 10, i);
		ft_putnbr(nb % 10, i);
	}
	else
		ft_putchar(nb + 48, i);
}
