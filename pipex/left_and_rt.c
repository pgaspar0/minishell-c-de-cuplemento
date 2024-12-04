/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_and_rt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:44:22 by jorcarva          #+#    #+#             */
/*   Updated: 2024/09/10 17:44:23 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	left2(char **av, int fd, int pipefd[2], char **envp)
{
	char	**arg;
	int		i;

	i = 0;
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	arg = ft_split(av[2], ' ');
	if (!arg)
		return (-1);
	if (ft_exec(arg, envp) == -1)
	{
		while (arg[i])
			free(arg[i++]);
		free(arg);
		return (-1);
	}
	while (arg[i])
		free(arg[i++]);
	free(arg);
	return (1);
}

int	rt2(char **av, int fd, int pipefd[2], char **envp)
{
	char	**arg;
	int		i;

	i = 0;
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	arg = ft_split(av[3], ' ');
	if (!arg)
		return (-1);
	if (ft_exec(arg, envp) == -1)
	{
		while (arg[i])
			free(arg[i++]);
		free(arg);
		return (-1);
	}
	while (arg[i])
		free(arg[i++]);
	free(arg);
	return (1);
}
