/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:33:16 by jorcarva          #+#    #+#             */
/*   Updated: 2025/02/06 07:36:30 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *envs, const char *key, int *flag)
{
	while (envs)
	{
		if (strcmp(envs->key, key) == 0)
		{
			*flag = 1;
			return (envs->value);
		}
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
	char	*value;
	char	*new_str;
	int		flag;
	int		key_len;

	flag = 0;
	key_len = is_valid_char(input, (pos + 1));
	if (key_len == 0)
		return (input);
	key = strndup(&input[pos + 1], key_len);
	value = get_env_value(envs, key, &flag);
	free(key);
	if (!value && flag == 0)
		return (input);
	else if (!value && flag == 1)
		value = "";
	new_str = malloc((strlen(input) - key_len + strlen(value)) + 1);
	if (!new_str)
		return (NULL);
	strncpy(new_str, input, pos);
	strcpy(new_str + pos, value);
	strcpy(new_str + pos + strlen(value), &input[pos + 1 + key_len]);
	free(input);
	return (new_str);
}

char	*expand_variables(char *input, t_env *envs)
{
	int	i;

	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
		{
			input = expand_variable(input, i, envs);
		}
		i++;
	}
	return (input);
}

char	*ft_expansion(const char *input, t_env *envs, int flag)
{
	char	*new_input;

	new_input = ft_strdup(input);
	if (has_squotes(input) && flag == 0)
		return (new_input);
	new_input = expand_variables(new_input, envs);
	return (new_input);
}
