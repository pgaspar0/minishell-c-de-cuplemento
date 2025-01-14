/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:58:02 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/14 11:58:10 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_status(t_env **envs, int status)
{
    char	*status_str;

    status_str = ft_itoa(status);
    update_env(envs, "?", status_str);
    free(status_str);
}