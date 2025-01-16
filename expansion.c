/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:33:16 by jorcarva          #+#    #+#             */
/*   Updated: 2025/01/16 11:18:20 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//#include <stddef.h>

int is_dquotes(const char *input) {
    int inside_quotes = 0;

    if (!input)
        return 0;
    while (*input) {
        if (*input == '"') {
            if (inside_quotes == 0)
                inside_quotes = 1;
            else
                inside_quotes = 0;
        }
        input++;
    }
    if (inside_quotes == 0)
        return 1;
    else
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

/* char    *ft_expansion(const char *input)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    if(is_dquotes(input) == 0)
        return (input);
    while(input[i])
    {
        if(input[i] == '$')
        {
            j = i;
            break;
        }
        i++;
    }
    if(input[j] == '$' && input[j+1] != '$')
        
} */
