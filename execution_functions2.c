/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:08:50 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/01 10:21:25 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_message(char **command)
{
	struct stat path_stat;

	ft_memset(&path_stat, 0, sizeof(struct stat));
	if (!command || !command[0])
		return;
	stat(command[0], &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else if (command[0][0] == '/')
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

void	cuta(t_shell *shell)
{
	char	*caminho;
	char	*path;
	char	**path_copy;

	if (!shell->current->args || !shell->current->args[0] || ft_strlen(shell->current->args[0]) == 0)
	{
		print_error_message(shell->current->args);
		exit(127);
	}
	path = ft_getenv("PATH", shell->envs);
	path_copy = ft_split(path, ':');
	caminho = get_caminho(path_copy, shell->current->args);
	if (!caminho)
	{
		print_error_message(shell->current->args);
		free_matrix(path_copy);
		exit(127);
	}
	execve(caminho, shell->current->args, shell->env_matrix);
	perror("Error");
	exit(1);
}
