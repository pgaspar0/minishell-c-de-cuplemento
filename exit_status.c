/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:58:02 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/14 19:02:20 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_status(t_env **envs, int status)
{
    char *status_str;

    if (WIFEXITED(status))
        status_str = ft_itoa(WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        status_str = ft_itoa(128 + WTERMSIG(status));
    else
        status_str = ft_strdup("1"); // Caso indefinido, considere erro genérico
    update_env(envs, "?", status_str);
    free(status_str);
}
