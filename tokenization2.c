/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:17:32 by jorcarva          #+#    #+#             */
/*   Updated: 2025/02/06 19:44:53 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**do_tokenize1(t_tokenizer *tk, size_t *i, int in_single_quote,
		int in_double_quote)
{
	char	quote;
	size_t	start;

	quote = tk->new_input[*i];
	start = ++(*i);
	while (tk->new_input[*i] && (tk->new_input[*i] != quote || in_single_quote
			|| in_double_quote))
	{
		if (tk->new_input[*i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (tk->new_input[*i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		(*i)++;
	}
	if (tk->new_input[*i] == quote)
		(*i)++;
	tk->tokens[tk->token_count++] = ft_substr(tk->new_input, start, *i - start
			- 1);
	return (tk->tokens);
}

void	do_tokenize2_aux(char *token, char *equal_sign, char *value)
{
	equal_sign = strchr(token, '=');
	if (equal_sign != NULL)
	{
		value = equal_sign + 1;
		if ((value[0] == '"' && value[strlen(value) - 1] == '"')
			|| (value[0] == '\'' && value[strlen(value) - 1] == '\''))
		{
			value[strlen(value) - 1] = '\0';
			memmove(value, value + 1, strlen(value));
		}
	}
}

char	**do_tokenize2(t_tokenizer *tk, size_t *i, int in_single_quote,
		int in_double_quote)
{
	char	*token;
	char	*equal_sign;
	char	*value;

	equal_sign = NULL;
	value = NULL;
	while (tk->new_input[*i] && (!ft_isspace(tk->new_input[*i])
			|| in_single_quote || in_double_quote))
	{
		if (tk->new_input[*i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (tk->new_input[*i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		(*i)++;
	}
	token = ft_substr(tk->new_input, tk->start, *i - tk->start);
	if (strchr(token, '=') != NULL && (strchr(token, '"') != NULL
			|| strchr(token, '\'') != NULL))
	{
		do_tokenize2_aux(token, equal_sign, value);
	}
	tk->tokens[tk->token_count++] = token;
	return (tk->tokens);
}
