/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:31:19 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/05 20:06:22 by jorcarva         ###   ########.fr       */
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

static int	are_quotes_balanced(const char *str)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*str)
	{
		if (*str == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (*str == '"' && single_quote == 0)
			double_quote = !double_quote;
		str++;
	}
	if (single_quote || double_quote)
		return (0);
	return (1);
}

int	tokenize2(t_tokenizer *tk, size_t i)
{
	i = 0;
	while (tk->new_input[i])
	{
		while (tk->new_input[i] && ft_isspace(tk->new_input[i]))
			i++;
		if (tk->new_input[i] == '\0')
			break ;
		tk->start = i;
		printf("valor de i: %ld\n",i);
		do_tokenize(&(*tk), &i);
	}
	return (i);
}

char	**tokenize(t_shell *shell)
{
	char		*expansion_result;
	t_tokenizer	tk;
	size_t		i;

	if (are_quotes_balanced(shell->input) == 0)
		return (NULL);
	expansion_result = ft_expansion(shell->input, shell->envs, 0);
	if (contains_dollar_sign(shell->input) && expansion_result)
		tk.new_input = ft_strdup(expansion_result);
	else
		tk.new_input = ft_strdup(shell->input);
	tk.tokens = ft_calloc(sizeof(char *), 1000000);
	if (!tk.tokens)
	{
		free(tk.new_input);
		return (NULL);
	}
	tk.token_count = 0;
	i = 0;
	i = tokenize2(&tk, i);
	tk.tokens[tk.token_count] = NULL;
	free(tk.new_input);
	free(expansion_result);
	return (tk.tokens);
}
