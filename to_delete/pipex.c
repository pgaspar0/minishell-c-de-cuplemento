/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:47:55 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/23 19:10:57 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	executa(char **command, char **envp)
{
	char	*caminho;
	char	*path;
	char	**path_copy;

	path = getenv("PATH");
	path_copy = ft_split(path, ':');
	caminho = get_caminho(path_copy, command);
	if (!caminho)
	{
		perror("Error");
		free_matrix(path_copy);
		exit(127);
	}
	execve(caminho, command, envp);
	perror("Error");
	exit(1);
}

/* void	here_doc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	while (ft_strncmp(delimiter, line, ft_strlen(delimiter)))
	{
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	free(line);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
} */
/* int	here_doc(char *delimiter)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	line = readline("heredoc> ");
	while (ft_strncmp(delimiter, line, ft_strlen(delimiter)))
	{
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putchar_fd('\n', pipe_fd[1]);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	return (0);
} */
/* void	keeping_up_main(char *av[], int *fd, int *i, int ac)
{
	if (!ft_strcmp(av[1], "here_doc"))
	{
		here_doc(av[2]);
		fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		*i = 3;
	}
	else
	{
		fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd[1] == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		fd[0] = open(av[1], O_RDONLY);
		if (fd[0] == -1)
		{
			close(fd[1]);
			perror("Error");
			exit(EXIT_FAILURE);
		}
		dup2(fd[0], 0);
		*i = 2;
	}
}

int	main(int ac, char *av[], char *envp[])
{
	int		i;
	int		fpid;
	int		fd[2];
	char	**command;
	char	**last_command;

	if (ac < 5)
		return (1);
	keeping_up_main(av, fd, &i, ac);
	last_command = ft_split(av[ac - 2], ' ');
	while (i < ac - 2)
	{
		command = ft_split(av[i], ' ');
		forka(command, envp);
		free_matrix(command);
		i++;
	}
	fpid = fork();
	if (fpid == 0)
		cuta_the_second(last_command, envp, fd[1]);
	else
		waitpid(fpid, NULL, 0);
	free_matrix(last_command);
	return (0);
} */
