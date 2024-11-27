/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:29:10 by jorcarva          #+#    #+#             */
/*   Updated: 2024/11/09 10:38:10 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  mat_len(char **mat)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(mat[i++]);
    while (mat[i])
    {
        len++;
        len += ft_strlen(mat[i]);
        i++;
    }
    return (i);
}

char    *mat_concat(char **mat)
{
    int     j;
    char    *str;

    j = 0;
    str = (char *)malloc(sizeof(char *) * mat_len(mat));
    while(mat[j])
    {
        str = ft_strjoin(str, mat[j]);;
        str = ft_strjoin(str, " ");
        j++;
    }
    return (str);
}