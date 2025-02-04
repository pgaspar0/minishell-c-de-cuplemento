/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hfuncs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:05:09 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/04 23:17:36 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_direct_command(char **command)
{
	int			status;
	struct stat	path_stat;

	status = access(command[0], X_OK | F_OK);
	if (status == 0)
	{
		stat(command[0], &path_stat);
		if (S_ISDIR(path_stat.st_mode))
			return (NULL);
		return (command[0]);
	}
	return (NULL);
}

char	*build_path(char *path, char *command)
{
	char	*temp;
	char	*caminho;

	temp = ft_strjoin(path, "/");
	caminho = ft_strjoin(temp, command);
	free(temp);
	return (caminho);
}

int	is_executable(char *caminho)
{
	int			status;
	struct stat	path_stat;

	status = access(caminho, X_OK | F_OK);
	if (status == 0)
	{
		stat(caminho, &path_stat);
		if (!S_ISDIR(path_stat.st_mode))
			return (1);
	}
	return (0);
}

char	*check_path_command(char **path_copy, char **command)
{
	int			i;
	char		*caminho;

	i = 0;
	while (path_copy && path_copy[i])
	{
		caminho = build_path(path_copy[i], command[0]);
		if (is_executable(caminho))
			return (caminho);
		free(caminho);
		i++;
	}
	return (NULL);
}

char	*get_caminho(char **path_copy, char **command)
{
	if (command[0][0] == '/' || (command[0][0] == '.' && command[0][1] == '/'))
		return (check_direct_command(command));
	return (check_path_command(path_copy, command));
}
