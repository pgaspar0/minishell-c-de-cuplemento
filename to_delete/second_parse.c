/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:45:10 by gamekiller2       #+#    #+#             */
/*   Updated: 2024/12/05 22:42:59 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_special(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

static size_t	ft_toklen(const char *s)
{
	size_t	ret;
	size_t	i;

	ret = 0;
	i = 0;
	while (s[i])
	{
		if (!is_special(s[i]))
		{
			++ret;
			while (s[i] && !is_special(s[i]))
				++i;
            if ((s[i] == '>' || s[i] == '<') && (s[i + 1] == '>' || s[i
                    + 1] == '<'))
                ++i;
		}
		else
			++i;
	}
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	len;

	if (s == 0)
		return (0);
	i = 0;
	ptr = malloc(sizeof(char *) * (ft_toklen(s, c) + 1));
	if (ptr == 0)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			ptr[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	ptr[i] = 0;
	return (ptr);
}