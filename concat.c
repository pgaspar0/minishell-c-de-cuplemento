/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:29:10 by jorcarva          #+#    #+#             */
/*   Updated: 2024/12/04 14:41:08 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *mat_concat(char **mat)
{
    char    *result;
    char    *temp;
    int     i;

    if (!mat || !mat[0])
        return (ft_strdup(""));
    result = ft_strdup("");
    if (!result)
        return (NULL);
    i = 0;
    while (mat[i])
    {
        temp = ft_strjoin(result, mat[i]);
        free(result);
        result = temp;
        if (mat[i + 1])
        {
            temp = ft_strjoin(result, " ");
            free(result);
            result = temp;
        }
        i++;
    }
    return (result);
}
