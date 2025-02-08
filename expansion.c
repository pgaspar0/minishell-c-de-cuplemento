/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:33:16 by jorcarva          #+#    #+#             */
/*   Updated: 2025/02/08 18:55:30 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *envs, const char *key)
{
	while (envs)
	{
		if (strcmp(envs->key, key) == 0)
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

int	is_valid_char(char *input, int i)
{
	int	key_len;

	key_len = 0;
	while ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a'
			&& input[i] <= 'z') || (input[i] >= '0' && input[i] <= '9')
		|| input[i] == '_' || input[i] == '?')
	{
		key_len++;
		i++;
	}
	return (key_len);
}

char	*expand_variable(char *input, int pos, t_env *envs)
{
	char	*key;
	char	*val;
	char	*new_str;
	int		len;

	len = is_valid_char(input, (pos + 1));
	if (len == 0)
		return (input);
	key = ft_strndup(&input[pos + 1], len);
	val = get_env_value(envs, key);
	free(key);
	if (!val)
		val = "";
	new_str = ft_calloc(sizeof(char), (ft_strlen(input) - len + ft_strlen(val))
			+ 5);
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, input, pos);
	ft_strcpy(new_str + pos, val);
	ft_strcpy(new_str + pos + strlen(val), &input[pos + 1 + len]);
	free(input);
	return (new_str);
}

char	*expand_variables(char *input, t_env *envs)
{
	int	i;

	i = -1;
	if (!input)
		return (NULL);
	while (input != NULL && input[++i])
		if (input[i] == '$')
			input = expand_variable(input, i, envs);
	return (input);
}

char	*ft_expansion(const char *input, t_env *envs, int flag)
{
	char	*new_input;

	if (!input)
		return (NULL);
	new_input = ft_strdup(input);
	if (has_squotes(input) && flag == 0)
		return (new_input);
	new_input = expand_variables(new_input, envs);
	return (new_input);
}
