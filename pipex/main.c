/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:50:19 by jorcarva          #+#    #+#             */
/*   Updated: 2024/11/09 11:34:25 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_exec(char *arg[], char **envp)
{
	char	*pathname;
	pid_t	pid;

	pathname = get_path_of_cmd(arg[0], envp);
	if (!pathname)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		free(pathname);
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(pathname, arg, NULL) == -1)
		{
			free(pathname);
			return (-1);
		}
	}
	waitpid(pid, NULL, 0);
	free(pathname);
	return (1);
}

int	left(char **av, int pipefd[2], char **envp)
{
	int		i;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	i = left2(av, fd, pipefd, envp);
	return (i);
}

int	right(char **av, int pipefd[2], char **envp)
{
	int		i;
	int		fd;

	fd = open(av[4], O_RDONLY | O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (-1);
	i = rt2(av, fd, pipefd, envp);
	return (i);
}

int	main(int ac, char **av, char **envp)
{
	int	pipefd[2];

	if (ac != 5 || !av[1][0] || !av[2][0] || !av[3][0] || !av[4][0])
	{
		ft_printf("\033[1;31mERROR: Not valid arguments.\033[0m\n");
		ft_printf("\033[1;31m<file1> <cmd1> <cmd2> <file2>\033[0m\n");
		return (-1);
	}
	if (pipe(pipefd) == -1)
	{
		ft_printf("\033[1;31mError creating pipe.\n");
		return (-1);
	}
	if (left(av, pipefd, envp) == -1)
	{
		perror("\033[1;31mError: primeiro comando\033[0m\n");
		return (-1);
	}
	if (right(av, pipefd, envp) == -1)
	{
		perror("\033[1;31mError: segundo comando\033[0m\n");
		return (-1);
	}
	return (0);
}
