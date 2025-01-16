/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:58:02 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/16 11:48:49 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_changer(int n)
{
	static int	status = 0;

	if (n != -1)
		status = n;
	return (status);
}

int	g_int(int n)
{
	static int	status_int = 0;

	if (n != -1)
		status_int = n;
	return (status_int);
}

void	update_exit_status(t_env **envs, int status)
{
	char	*status_str;

	if (WIFEXITED(status))
		g_status_changer(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		g_status_changer(128 + WTERMSIG(status));
	else
		g_status_changer(1);
	status_str = ft_itoa(g_status_changer(-1));
	update_env(envs, "?", status_str);
	free(status_str);
}
