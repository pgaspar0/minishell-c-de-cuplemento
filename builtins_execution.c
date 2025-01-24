/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:33 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/23 19:44:44 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **args, t_env **envs)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		if (!args[2])
			ret = ft_cd(args, *envs);
		else
		{
			ret = 1;
			printf("Error: too many arguments\n");
		}
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(args[0], "env") == 0)
	{
		update_exit_status(envs, g_status_changer(-1));
		ft_env(*envs);
	}
	else if (ft_strcmp(args[0], "export") == 0)
	{
		if (!args[1])
			ft_export_no(envs);
		else
			ft_export_multiple(envs, args);
	}
	else if (ft_strcmp(args[0], "unset") == 0)
	{	
		if (!args[1])
			return (0);
		ft_unset_multiple(envs, args);
	}
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(envs, args, NULL);
	return (ret);
}
