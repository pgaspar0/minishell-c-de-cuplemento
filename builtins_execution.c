/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:33 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/13 18:15:49 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(char **args, t_env **envs)
{
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		if (!args[2])
			ft_cd(args);
		else
			printf("Error: too many arguments\n");
	}
	//else if (ft_strcmp(args[0], "pwd") == 0) */
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env(*envs);
    else if (ft_strcmp(args[0], "export") == 0)
		ft_export(envs, args[1]);	
	/*
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, envp);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args); */
}
