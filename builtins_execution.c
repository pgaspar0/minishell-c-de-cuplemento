/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:33 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/03 15:55:52 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin2(t_shell *shell, char **args)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(args[0], "env") == 0)
	{
		update_exit_status(&shell->envs, g_status_changer(-1));
		ft_env(shell->envs);
	}
	else if (ft_strcmp(args[0], "export") == 0)
	{
		if (!args[1])
			ft_export_no(&shell->envs);
		else
			ft_export_multiple(&shell->envs, args);
	}
	else if (ft_strcmp(args[0], "unset") == 0)
	{	
		if (!args[1])
			return (0);
		ft_unset_multiple(&shell->envs, args);
	}
	else if (ft_strcmp(args[0], "exit") == 0)
		ret = ft_exit(&shell->envs, args, NULL, shell);
	return (ret);
}

int	execute_builtin(t_shell *shell, char **args)
{
	int	ret;

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
	else 
		return(execute_builtin2(shell, args));
	return (ret);
}
