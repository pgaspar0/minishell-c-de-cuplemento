/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:33:16 by jorcarva          #+#    #+#             */
/*   Updated: 2025/02/03 15:54:27 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(t_env *envs, const char *key, int *flag)
{
    while (envs)
    {
        if (strcmp(envs->key, key) == 0)
        {
            *flag = 1;
            return envs->value;
        }
        envs = envs->next;
    }
    return NULL;
}
int is_valid_char(char *input, int i)
{
    int key_len;

    while ((input[i] >= 'A' && input[i] <= 'Z') || 
           (input[i] >= 'a' && input[i] <= 'z') || 
           (input[i] >= '0' && input[i] <= '9') || 
           input[i] == '_' || input[i] == '?')
    {
        key_len++;
        i++;
    }
    return key_len;
}

char *expand_variable(char *input, int pos, t_env *envs)
{
    int flag;
    int i = pos + 1;
    int key_len = 0;

    key_len = is_valid_char(input, i);
    if (key_len == 0)
        return input;
    char *key = strndup(&input[pos + 1], key_len);
    flag = 0;
    char *value = get_env_value(envs, key, &flag);
    free(key);
    if (!value && flag == 0)
        return input;
    else if (!value && flag == 1)
        value = "";
    int new_len = strlen(input) - key_len + strlen(value);
    char *new_str = malloc(new_len + 1);
    if (!new_str)
        return NULL;
    strncpy(new_str, input, pos);
    strcpy(new_str + pos, value);
    strcpy(new_str + pos + strlen(value), &input[pos + 1 + key_len]);
    free(input);
    return new_str;
}

char *expand_variables(char *input, t_env *envs)
{
    int i = 0;

    if (!input)
        return (NULL);
    while (input[i]) {
        if (input[i] == '$') {
            input = expand_variable(input, i, envs);
        }
        i++;
    }
    return input;
}

char    *ft_expansion(const char *input, t_env *envs, int flag)
{
    char    *new_input;

    new_input = ft_strdup(input);
    if (has_squotes(input) && flag == 0)
        return (new_input);
    printf("Chegou aqui\n");
    new_input = expand_variables(new_input, envs);
    return(new_input);
}
