/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:33:16 by jorcarva          #+#    #+#             */
/*   Updated: 2025/01/27 20:03:36 by jorcarva         ###   ########.fr       */
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

static char *replace_key(const char *input, const char *key, t_env *envs)
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
            //printf("value: %s\n", value);
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
    //printf("new_str: %s\n", new_str);
    return new_str;
}

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
    while (input[j] && input[j] != ' ' && input[j] != '\t' && input[j] != '"' && input[j] != '$' && input[j] != '\'')
        j++;
    key = (char *)malloc(sizeof(char) * (j - i + 1));
    if (!key)
        return NULL;
    strncpy(key, &input[i], j - i);
    key[j - i] = '\0';
    //printf("key: %s\n", key);
    return key;
}

static int count_dsign(const char *input)
{
    int count = 0;
    while (*input) {
        if (*input == '$' && *input + 1 == '$')
        {
                //printf("\ninput dentro do while que pula:%s\n",input);
            while (*input == '$'){
                input++;
            }
        }
        else if (*input == '$' && *input + 1 != '$' && *input - 1 != '$') {
            const char *next = input + 1;
            //printf("next value: %s\n",next);
            if (*next && *next != ' ' && *next != '\t' && *next != '$' && *next - 1 != '$' && *next + 1 != '$') {
                count++;
            }
        }
        input++;
    }
    return count;
}

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

static char    *ft_expansion2(const char *input, t_env *envs)
{
    char *key;
    //char    *str;
    int i;
    int j;
    int k;
    
    i = 0;
    j = 0;
    k = 0;
    //printf("\ndquotes result : %d \n",is_dquotes(input));
    while(input[i])
    {
        if(input[i] == '$')
        {
            //printf("%s",extract_key(input));
            j = i + 1;
            break;
        }
        i++;
    }
    while(input[j] && input[j] != ' ' && input[j] != '\t')
        j++;
    //printf("\033[1;31mChegou aqui, linha 170, file expansion.c\033[0m\n");
    key = (char *)malloc(sizeof(char) * (j - i + 1));
    i++;
    while(i != j)
        key[k++] = input[i++];
    key = replace_key(input, extract_key(input), envs);
    //printf("teste dentro da func ft_expansion2, 178: %s\n",key);
    return(key);
}

char    *ft_expansion(const char *input, t_env *envs)
{
    int i;
    char    *new_input;

    //printf("tem single quotes or not: %d\n",has_squotes(input));
    new_input = ft_strdup(input);
    if (has_squotes(input))
        return (new_input);
    i = count_dsign(input);
    //printf("Tem %d dollar signs\n",i);
    if(i--)
        new_input = ft_expansion2(input, envs);
    //printf("new input1: %s\n",new_input);
    while(i--)
    {
        if (ft_expansion2(new_input, envs))
            new_input = ft_expansion2(new_input, envs);
        //printf("new input 2: %s\n",new_input);
    }
    return(new_input);
}

// char *ft_expansion(const char *input, t_env *envs)
// {
//     char *result;
//     char *key;
//     char *expanded_str;
//     int i = 0, k = 0;
//     int result_len = 0;

//     if (!input)
//         return NULL;

//     result = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
//     if (!result)
//         return NULL;

//     while (input[i])
//     {
//         if (input[i] == '$')
//         {
//             key = extract_key(&input[i]);
//             if (key)
//             {
//                 expanded_str = replace_key(input, key, envs);
//                 if (expanded_str)
//                 {
//                     result_len += ft_strlen(expanded_str);
//                     result = (char *)realloc(result, result_len + 1);
//                     if (!result)
//                     {
//                         free(key);
//                         free(expanded_str);
//                         return NULL;
//                     }
//                     strcpy(&result[k], expanded_str);
//                     k += ft_strlen(expanded_str);
//                     i += ft_strlen(key) + 1;
//                     free(expanded_str);
//                 }
//                 else
//                 {
//                     free(key);
//                     free(result);
//                     return NULL;
//                 }
//                 free(key);
//             }
//         }
//         else
//         {
//             result[k++] = input[i++];
//         }
//     }
//     result[k] = '\0';
//     return result;
// }
