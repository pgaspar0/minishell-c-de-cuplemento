/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:31:19 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/22 08:30:29 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_tokenize(t_tokenizer *tk, size_t *i)
{
	tk->quoted = (tk->new_input[*i] == '\'' || tk->new_input[*i] == '"');
	if (tk->quoted)
	{
		skip_quotes(tk->new_input, i, tk->new_input[*i]);
		tk->tokens[tk->token_count++] = ft_substr(tk->new_input, tk->start + 1,
				*i - tk->start - 2);
	}
	else if (is_special_char(tk->new_input[*i]))
	{
		(*i)++;
		if ((tk->new_input[tk->start] == '<' || tk->new_input[tk->start] == '>')
			&& tk->new_input[*i] == tk->new_input[tk->start])
			(*i)++;
		tk->tokens[tk->token_count++] = ft_substr(tk->new_input, tk->start, *i
				- tk->start);
	}
	else
	{
		while (tk->new_input[*i] && !ft_isspace(tk->new_input[*i])
			&& !is_special_char(tk->new_input[*i]))
			(*i)++;
		tk->tokens[tk->token_count++] = ft_substr(tk->new_input, tk->start, *i
				- tk->start);
	}
}

char	**tokenize(const char *input, t_env *envs)
{
	t_tokenizer	tk;
	size_t		i;

	if (contains_dollar_sign(input) && is_dquotes(input) && ft_expansion(input,
			envs))
		tk.new_input = ft_expansion(input, envs);
	else
		tk.new_input = ft_strdup(input);
	tk.tokens = malloc(sizeof(char *) * 1024);
	if (!tk.tokens)
		return (NULL);
	tk.token_count = 0;
	i = 0;
	while (tk.new_input[i])
	{
		while (tk.new_input[i] && ft_isspace(tk.new_input[i]))
			i++;
		if (tk.new_input[i] == '\0')
			break ;
		tk.start = i;
		do_tokenize(&tk, &i);
	}
	tk.tokens[tk.token_count] = NULL;
	return (tk.tokens);
}
