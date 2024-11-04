/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:52:24 by pgaspar           #+#    #+#             */
/*   Updated: 2024/06/06 09:56:03 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*junte(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = -1;
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (get_strlen(s1) + get_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[++j] != '\0')
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free (s1);
	return (str);
}

static char	*pux_all(int fd, char *all)
{
	int		n;
	char	*buffer;

	n = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while ((!get_strchr(all, '\n')) && (n != 0))
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[n] = '\0';
		all = junte(all, buffer);
		if (!all)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (all);
}

static char	*pux_line(char	*all)
{
	char	*s;
	int		i;

	i = 0;
	if (!all[i])
		return (NULL);
	while (all[i] != '\0' && all[i] != '\n')
		i++;
	s = malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (all[i] != '\0' && all[i] != '\n')
	{
		s[i] = all[i];
		i++;
	}
	if (all[i] == '\n')
	{
		s[i] = all[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

static char	*xo(char *all)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (all[i] != '\0' && all[i] != '\n')
		i++;
	if (!all[i])
	{
		free(all);
		return (NULL);
	}
	s = malloc(sizeof(char) * (get_strlen(all) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (all[i] != '\0')
		s[j++] = all[i++];
	s[j] = '\0';
	free(all);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*all;
	char		*s;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	all = pux_all(fd, all);
	if (!all)
		return (NULL);
	s = pux_line(all);
	all = xo(all);
	return (s);
}
