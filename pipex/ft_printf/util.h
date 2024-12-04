/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:57:18 by jorcarva          #+#    #+#             */
/*   Updated: 2024/05/30 09:57:34 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdlib.h>
# include <unistd.h>

void	ft_char(char c, int *tamanho);
void	ft_hex_lower(unsigned int num, int *tamanho);
void	ft_hex_upper(unsigned int num, int *tamanho);
void	ft_int(int n, int *tamanho);
void	ft_pointer(void *ptr, int *tamanho);
void	ft_string(char *str, int *tamanho);
void	ft_unsigned(unsigned int num, int *tamanho);

#endif
