/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:57:11 by jorcarva          #+#    #+#             */
/*   Updated: 2024/08/14 12:57:53 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_from_envp(char **envp)
{
	int	i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	return (envp[i] + 5);
}

static void	freers(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

char	*get_path_of_cmd(char *cmd, char **envp)
{
	int		i;
	char	*half_path;
	char	*full_path;
	char	**paths;

	i = 0;
	paths = ft_split(get_path_from_envp(envp), ':');
	while (paths[i])
	{
		half_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			freers(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	freers(paths);
	return (NULL);
}
