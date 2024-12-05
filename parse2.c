/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:52:31 by pgaspar           #+#    #+#             */
/*   Updated: 2024/12/05 04:59:43 by gamekiller2      ###   ########.fr       */
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
			if ((s[i] == '>' || s[i] == '<') && (s[i + 1] == '>' || s[i
					+ 1] == '<'))
				++i;
			while (s[i] && !is_special(s[i]))
				++i;
			if (is_special(s[i]))
				++ret;
		}
		else
			++i;
	}
	return (ret);
}

char	**ft_parse2(const char *s)
{
	char	**ptr;
	size_t	i;
	size_t	len;

	if (s == 0)
		return (0);
	i = 0;
	ptr = malloc(sizeof(char *) * (ft_toklen(s) + 1));
	if (ptr == 0)
		return (0);
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			++s;
		if (!*s)
			break ;
		if (!is_special(*s))
		{
			len = 0;
			while (*s && (!is_special(*s)) && ++len)
				++s;
			ptr[i++] = ft_substr(s - len, 0, len);
		}
		else if (is_special(*s))
		{
			len = 0;
			while (*s && (is_special(*s)))
			{
				++len;
				++s;
			}
			ptr[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	ptr[i] = 0;
	return (ptr);
}
