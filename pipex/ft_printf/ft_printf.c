/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:27:50 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/30 09:29:35 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_formato(va_list args, const char formato, int *tamanho)
{
	if (formato == 'c')
		ft_char((char)va_arg(args, int), tamanho);
	else if (formato == 's')
		ft_string(va_arg(args, char *), tamanho);
	else if (formato == 'd' || formato == 'i')
		ft_int(va_arg(args, int), tamanho);
	else if (formato == 'X')
		ft_hex_upper(va_arg(args, unsigned int), tamanho);
	else if (formato == 'x')
		ft_hex_lower(va_arg(args, unsigned int), tamanho);
	else if (formato == 'p')
		ft_pointer(va_arg(args, void *), tamanho);
	else if (formato == 'u')
		ft_unsigned(va_arg(args, unsigned int), tamanho);
	else if (formato == '%')
		ft_char('%', tamanho);
}

int	ft_printf(const char *formato, ...)
{
	va_list	args;
	int		tamanho;

	tamanho = 0;
	va_start(args, formato);
	while (*formato)
	{
		if (*formato == '%')
		{
			formato++;
			ft_formato(args, *formato, &tamanho);
		}
		else
			ft_char(*formato, &tamanho);
		formato++;
	}
	va_end(args);
	return (tamanho);
}
