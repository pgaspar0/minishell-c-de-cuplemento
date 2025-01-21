/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_builtins2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:53:26 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/21 07:34:03 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_multiple(t_env **env, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_unset(env, args[i]);
		i++;
	}
}

void	ft_export_multiple(t_env **env, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_export(env, args[i]);
		i++;
	}
}
