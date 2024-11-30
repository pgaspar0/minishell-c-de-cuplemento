/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:52:31 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/29 11:52:58 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_special(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t')
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
			if (s[i] == '>' || s[i] == '<')
				++i;
			while (s[i] && !is_special(s[i]))
				++i;
			if (is_special(s[i]) && (s[i] != ' ' && s[i] != '\t'))
				++ret;
		}
		else
			++i;
	}
	return (ret);
}

char	**ft_parse(const char *s)
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
		if (!is_special(*s))
		{
			len = 0;
			while (*s && (!is_special(*s)) && ++len)
				++s;
			ptr[i++] = ft_substr(s - len, 0, len);
		}
		else if (is_special(*s) && (*s != ' ' && *s != '\t'))
		{
			len = 0;
			while (*s && (is_special(*s) && (*s != ' ' && *s != '\t')))
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
