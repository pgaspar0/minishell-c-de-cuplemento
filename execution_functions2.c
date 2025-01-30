/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:08:50 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/28 14:59:25 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_message(char **command)
{
	if (command[0][0] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void	cuta(char **command, char **envp, t_env *envs)
{
	char	*caminho;
	char	*path;
	char	**path_copy;

	if (!command || !command[0] || ft_strlen(command[0]) == 0)
	{
		print_error_message(command);
		exit(127);
	}
	path = ft_getenv("PATH", envs);
	path_copy = ft_split(path, ':');
	caminho = get_caminho(path_copy, command);
	if (!caminho)
	{
		print_error_message(command);
		free_matrix(path_copy);
		exit(127);
	}
	execve(caminho, command, envp);
	perror("Error");
	exit(1);
}
