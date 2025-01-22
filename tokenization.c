/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:31:19 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/22 16:22:51 by pgaspar          ###   ########.fr       */
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

char	**tokenize(t_shell *shell)
{
	t_tokenizer	tk;
	size_t		i;

	if (contains_dollar_sign(shell->input) && is_dquotes(shell->input) && ft_expansion(shell->input,
			shell->envs))
		tk.new_input = ft_expansion(shell->input, shell->envs);
	else
		tk.new_input = ft_strdup(shell->input);
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
