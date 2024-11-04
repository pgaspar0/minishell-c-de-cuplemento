/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:32:06 by pgaspar           #+#    #+#             */
/*   Updated: 2024/05/26 13:11:52 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_it(const char p, va_list al, int *c)
{
	if (p == 'd' || p == 'i')
		ft_putnbr(va_arg(al, int), c);
	else if (p == 'c')
		ft_putchar((char)va_arg(al, int), c);
	else if (p == 'u')
		ft_unsigned(va_arg(al, unsigned int), c);
	else if (p == '%')
		ft_putchar('%', c);
	else if (p == 's')
		ft_putstr(va_arg(al, char *), c);
	else if (p == 'X')
		int_to_hex_upper(va_arg(al, unsigned int), c);
	else if (p == 'x')
		int_to_hex_lower(va_arg(al, unsigned int), c);
	else if (p == 'p')
		print_pointer(va_arg(al, void *), c);
}

int	ft_printf(const char *p, ...)
{
	va_list	al;
	int		i;

	i = 0;
	va_start(al, p);
	while (*p)
	{
		if (*p == '%')
		{
			p++;
			print_it(*p, al, &i);
		}
		else
			ft_putchar(*p, &i);
		p++;
	}
	va_end(al);
	return (i);
}
