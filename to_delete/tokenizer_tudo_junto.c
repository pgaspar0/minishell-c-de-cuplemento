/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tudo_junto.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:15:23 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/22 08:15:37 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* char	**tokenize(const char *input, t_env *envs)
{
	char **tokens;
	char *new_input;
	size_t token_count;
	size_t start;
	size_t i;
	bool quoted;

	 if(contains_dollar_sign(input) && is_dquotes(input) && ft_expansion(input, envs))
		new_input = ft_expansion(input, envs);
	else
		new_input = ft_strdup(input);
	//printf("\n n_input: %s\n",new_input);
	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
		return (NULL);
	token_count = 0;
	i = 0;
	while (new_input[i])
	{
		while (new_input[i] && ft_isspace(new_input[i]))
			i++;
		if (new_input[i] == '\0')
			break ;
		start = i;
		quoted = (new_input[i] == '\'' || new_input[i] == '"');
		if (quoted)
		{
			skip_quotes(new_input, &i, new_input[i]);
			tokens[token_count++] = ft_substr(new_input, start + 1, i - start - 2);
		}
		else if (is_special_char(new_input[i]))
		{
			i++;
			if ((new_input[start] == '<' || new_input[start] == '>')
				&& new_input[i] == new_input[start])
				i++;
			tokens[token_count++] = ft_substr(new_input, start, i - start);
		}
		else
		{
			while (new_input[i] && !ft_isspace(new_input[i])
				&& !is_special_char(new_input[i]))
				i++;
			tokens[token_count++] = ft_substr(new_input, start, i - start);
		}
	}
	tokens[token_count] = NULL;
	return (tokens);
} */