/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:08:50 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/08 17:29:18 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_message(char **command)
{
	struct stat	path_stat;

	ft_memset(&path_stat, 0, sizeof(struct stat));
	if (!command || !command[0])
		return ;
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

int	error_check(t_shell *shell)
{
	if (!shell->current->args || !shell->current->args[0])
		return (1);
	else if (ft_strlen(shell->current->args[0]) == 0)
		return (1);
	return (0);
}

void	do_execute(t_shell *shell)
{
	shell->env_matrix = env_to_matrix(shell->envs);
	shell->ret = cuta(shell);
	free_all(shell);
	free_matrix(shell->env_matrix);
	exit(shell->ret);
}

int	cuta(t_shell *shell)
{
	char	*caminho;
	char	*path;
	char	**path_copy;

	if (error_check(shell))
	{
		print_error_message(shell->current->args);
		return (127);
	}
	path = ft_getenv("PATH", shell->envs);
	path_copy = ft_split(path, ':');
	free(path);
	caminho = get_caminho(path_copy, shell->current->args);
	if (!caminho)
	{
		print_error_message(shell->current->args);
		free_matrix(path_copy);
		return (127);
	}
	if (execve(caminho, shell->current->args, shell->env_matrix) == -1)
	{
		perror("Error");
		return (1);
	}
	return (0);
}
