/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:37 by jorcarva          #+#    #+#             */
/*   Updated: 2025/02/03 15:41:41 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_dquotes(const char *input)
{
    if (!input)
        return 0;
    while (*input) {
        if (*input == '"')
            return 1;
        input++;
    }
    return 0;
}

int contains_dollar_sign(const char *input)
{
    if (!input)
        return 0;
    while (*input) {
        if (*input == '$')
            return 1;
        input++;
    }
    return 0;
}

int is_env_var(t_env *envs, char *key)
{
    while(envs)
    {
        if (strcmp(envs->key, key) == 0)
            return 1;
        envs = envs->next;
    }
    return 0;
}

char *extract_key(const char *input)
{
    char *key;
    int i = 0, j = 0;

    if (!input)
        return NULL;
    while (input[i] && input[i] != '$')
        i++;
    if (!input[i] || input[i] != '$')
        return NULL;
    i++;
    j = i;
    while (input[j] && input[j] != ' ' && input[j] != '\t' && input[j] != '$' && input[j] != '"' && input[j] != '\'')
        j++;
    key = (char *)malloc(sizeof(char) * (j - i + 1));
    if (!key)
        return NULL;
    strncpy(key, &input[i], j - i);
    key[j - i] = '\0';
    return key;
}

int has_squotes(const char *str)
{
    int count = 0;

    while (*str) {
        if (*str == '\'')
            count++;
        str++;
    }
    if(count != 0)
        return (count % 2 == 0);
    return (0);
}
