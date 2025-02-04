/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hfuncs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:05:09 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/03 19:05:43 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_caminho(char **path_copy, char **command)
{
	int			i;
	int			status;
	char		*temp;
	char		*caminho;
	struct stat	path_stat;

	i = 0;
	if (command[0][0] == '/' || (command[0][0] == '.' && command[0][1] == '/'))
	{
		status = access(command[0], X_OK | F_OK);
		if (status == 0)
		{
			stat(command[0], &path_stat);
			if (S_ISDIR(path_stat.st_mode))
				return (NULL);
			return (command[0]);
		}
		else
			return (NULL);
	}
	while (path_copy && path_copy[i])
	{
		temp = ft_strjoin(path_copy[i], "/");
		caminho = ft_strjoin(temp, command[0]);
		free(temp);
		status = access(caminho, X_OK | F_OK);
		if (status == 0)
		{
			stat(caminho, &path_stat);
			if (S_ISDIR(path_stat.st_mode))
			{
				free(caminho);
				return (NULL);
			}
			return (caminho);
		}
		free(caminho);
		i++;
	}
	return (NULL);
}
