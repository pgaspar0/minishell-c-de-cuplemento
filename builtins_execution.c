/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:33 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/17 17:16:07 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **args, t_env **envs)
{
	int ret;

	ret = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		if (!args[2])
			ret = ft_cd(args);
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
		ft_export(envs, args[1]);
	/*
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, envp);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args); */
	return (ret);
}
