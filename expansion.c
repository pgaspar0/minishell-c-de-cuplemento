/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:33:16 by jorcarva          #+#    #+#             */
/*   Updated: 2025/02/03 13:28:16 by pgaspar          ###   ########.fr       */
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

// static char * replace_key(const char *input, const char *key, t_env *envs)
// {
//     char *new_str;
//     char *value = NULL;
//     int i = 0, j = 0, k = 0;
//     int new_len;

//     // Find the value corresponding to the key in the envs list
//     while (envs && envs->key && key)
//     {
//         if (strcmp(envs->key, key) == 0)
//         {
//             value = envs->value;
//             //printf("value: %s\n", value);
//             break;
//         }
//         envs = envs->next;
//     }
//     if (!value)
//         return NULL;
//     new_len = ft_strlen(input) - ft_strlen(key) + ft_strlen(value);
//     //printf("tamanho do value: %i\n",new_len);
//     new_str = (char *)malloc(sizeof(char) * (new_len + 1));
//     if (!new_str)
//         return NULL;

//     while (input[i])
//     {
//         if (input[i] == '$' && strncmp(&input[i + 1], key, ft_strlen(key)) == 0)
//         {
//             i += ft_strlen(key) + 1;
//             while (value[k])
//                 new_str[j++] = value[k++];
//         }
//         else
//         {
//             new_str[j++] = input[i++];
//         }
//     }
//     new_str[j] = '\0';
//     //printf("new_str: %s\n", new_str);
//     return new_str;
// }

char *extract_key(const char *input) {
    char *key;
    int i = 0, j = 0;

    //printf("Passou aqui\n");
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
    //printf("key: %s\n", key);
    return key;
}

// static int count_dsign(const char *input)
// {
//     int count = 0;
//     while (*input) {
//         if (*input == '$' && *input + 1 == '$')
//         {
//                 //printf("\ninput dentro do while que pula:%s\n",input);
//             while (*input == '$'){
//                 input++;
//             }
//         }
//         else if (*input == '$' && *input + 1 != '$' && *input - 1 != '$') {
//             const char *next = input + 1;
//             //printf("next value: %s\n",next);
//             if (*next && *next != ' ' && *next != '\t' && *next != '$' && *next - 1 != '$' && *next + 1 != '$') {
//                 count++;
//             }
//         }
//         input++;
//     }
//     return count;
// }

int has_squotes(const char *str) {
    int count = 0;

    while (*str) {
        if (*str == '\'')
            count++;
        str++;
    }
    // Retorna 1 se a quantidade for par, 0 caso contrário
    if(count != 0)
        return (count % 2 == 0);
    return (0);
}

    //ft_expansion2, após declaração
    //printf("\ndquotes result : %d \n",is_dquotes(input));
    // printf("\033[1;31mChegou aqui, linha 170, file expansion.c\033[0m\n");
    // while(input[i])
    // {
    //     if(input[i] == '$')
    //     {
    //         //printf("%s",extract_key(input));
    //         break;
    //     }
    //     i++;
    // }

// static char    *ft_expansion2(const char *input, t_env *envs, int i)
// {
//     char *key;
//     int j;
//     int k;
    
//     k = 0;
//     j = i + 1;
//     while(input[j] && input[j] != ' ' && input[j] != '\t')
//         j++;
//     key = (char *)malloc(sizeof(char) * (j - i + 1));
//     i++;
//     while(i != j)
//         key[k++] = input[i++];
//     key = replace_key(input, extract_key(input), envs);
//     //printf("teste dentro da func ft_expansion2, 178: %s\n",key);
//     if (!key)
//         return(free(key), NULL);
//     return(key);
// }

//TESTANDO CORREÇÃO DO CODIGO ABAIXO:
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

char *expand_variable(char *input, int pos, t_env *envs)
{
    int flag;
    int i = pos + 1;
    int key_len = 0;

    while ((input[i] >= 'A' && input[i] <= 'Z') || 
           (input[i] >= 'a' && input[i] <= 'z') || 
           (input[i] >= '0' && input[i] <= '9') || 
           input[i] == '_' || input[i] == '?')
    {
        key_len++;
        i++;
    }
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

char *expand_variables(char *input, t_env *envs) {
    int i = 0;

    while (input[i]) {
        if (input[i] == '$') {
            input = expand_variable(input, i, envs);
        }
        i++;
    }
    return input;
}
//CORREÇÃO DE CODIGO TESTADA ACIMA.

char    *ft_expansion(const char *input, t_env *envs, int flag)
{
    char    *new_input;

    //printf("tem single quotes or not: %d\n",has_squotes(input));
    new_input = ft_strdup(input);
    if (has_squotes(input) && flag == 0)
        return (new_input);
    new_input = expand_variables(new_input, envs);
    // printf("%s\n", new_input);
    return(new_input);
}
