/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undefined_class.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:39:31 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/09 12:58:26 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_quotes(const char *input, size_t *index, char quote)
{
	(*index)++;
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (input[*index] == quote)
		(*index)++;
}

bool	validate_syntax(char **tokens)
{
	for (int i = 0; tokens[i]; i++)
	{
		if (is_special_char(tokens[i][0]))
		{
			if (tokens[i][1] != '\0' && (tokens[i][0] != '<'
					&& tokens[i][0] != '>'))
				return (false);
			if (i == 0 || !tokens[i + 1] || is_special_char(tokens[i + 1][0]))
				return (false);
		}
	}
	return (true);
}

int	open_file(const char *filename, int flags, int mode)
{
	int fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	return (fd);
}