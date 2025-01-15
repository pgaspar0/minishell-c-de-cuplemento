/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:31:19 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/15 20:53:19 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenize(const char *input)
{
	char **tokens;
	size_t token_count;
	size_t start;
	size_t i;
	bool quoted;

	if(contains_dollar_sign(input))
		ft_expansion(input);
	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
		return (NULL);
	token_count = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		start = i;
		quoted = (input[i] == '\'' || input[i] == '"');
		if (quoted)
		{
			skip_quotes(input, &i, input[i]);
			tokens[token_count++] = ft_substr(input, start + 1, i - start - 2);
		}
		else if (is_special_char(input[i]))
		{
			i++;
			if ((input[start] == '<' || input[start] == '>')
				&& input[i] == input[start])
				i++;
			tokens[token_count++] = ft_substr(input, start, i - start);
		}
		else
		{
			while (input[i] && !ft_isspace(input[i])
				&& !is_special_char(input[i]))
				i++;
			tokens[token_count++] = ft_substr(input, start, i - start);
		}
	}
	tokens[token_count] = NULL;
	return (tokens);
}
