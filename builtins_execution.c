/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:47:33 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/03 14:00:29 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_shell *shell)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(shell->tokens[0], "echo") == 0)
		ft_echo(shell->tokens);
	else if (ft_strcmp(shell->args[0], "cd") == 0)
	{
		if (!shell->args[2])
			ret = ft_cd(shell->args, shell->envs);
		else
		{
			ret = 1;
			printf("Error: too many arguments\n");
		}
	}
	else if (ft_strcmp(shell->args[0], "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(shell->args[0], "env") == 0)
	{
		update_exit_status(&shell->envs, g_status_changer(-1));
		ft_env(shell->envs);
	}
	else if (ft_strcmp(shell->args[0], "export") == 0)
	{
		if (!shell->args[1])
			ft_export_no(&shell->envs);
		else
			ft_export_multiple(&shell->envs, shell->args);
	}
	else if (ft_strcmp(shell->args[0], "unset") == 0)
	{	
		if (!shell->args[1])
			return (0);
		ft_unset_multiple(&shell->envs, shell->args);
	}
	else if (ft_strcmp(shell->args[0], "exit") == 0)
		ret = ft_exit(&shell->envs, shell->args, NULL, shell);
	return (ret);
}
