/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:33:16 by jorcarva          #+#    #+#             */
/*   Updated: 2025/01/16 19:16:32 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//#include <stddef.h>

int is_dquotes(const char *input) {
    if (!input)
        return 0;
    while (*input) {
        if (*input == '"')
            return 1;
        input++;
    }
    return 0;
}

int contains_dollar_sign(const char *input) {
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

static char *replace_key(const char *input, char *key, t_env *envs)
{
    char *new_str;
    char *value = NULL;
    int i = 0, j = 0, k = 0;
    int new_len;

    // Find the value corresponding to the key in the envs list
    while (envs)
    {
        if (strcmp(envs->key, key) == 0)
        {
            value = envs->value;
            break;
        }
        envs = envs->next;
    }

    if (!value)
        return NULL;

    new_len = ft_strlen(input) - ft_strlen(key) + ft_strlen(value);
    new_str = (char *)malloc(sizeof(char) * (new_len + 1));
    if (!new_str)
        return NULL;

    while (input[i])
    {
        if (input[i] == '$' && strncmp(&input[i + 1], key, ft_strlen(key)) == 0)
        {
            i += ft_strlen(key) + 1;
            while (value[k])
                new_str[j++] = value[k++];
        }
        else
        {
            new_str[j++] = input[i++];
        }
    }
    new_str[j] = '\0';
    return new_str;
}

char    *ft_expansion(const char *input, t_env *envs)
{
    char *key;
    int i;
    int j;
    int k;
    
    i = 0;
    j = 0;
    k = 0;
    printf("\ndquotes result : %d \n",is_dquotes(input));
    while(input[i])
    {
        if(input[i] == '$')
        {
            j = i + 1;
            break;
        }
        i++;
    }
    while(input[j] != ' ' && input[j] != '\t')
        j++;
    key = (char *)malloc(sizeof(char) * (j - i + 1));
    i++;
    while(i != j)
        key[k++] = input[i++];
    //printf("teste dentro da func: %s\n",key);
    key = replace_key(input, "USERLOG", envs);
    return(key);
}
