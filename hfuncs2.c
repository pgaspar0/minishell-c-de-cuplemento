/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hfuncs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:44:07 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/16 11:51:16 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	just_execute(char **command, char **envp)
{
	int	fpid;

	fpid = fork();
	if (fpid == 0)
		cuta(command, envp);
	else
		waitpid(fpid, NULL, 0);
}

void	pipe_it(char **command, char **envp)
{
	int	fpid;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		return ;
	}
	fpid = fork();
	if (fpid == 0)
		cuta_in_between(command, envp, pipe_fd);
	else
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		waitpid(fpid, NULL, 0);
	}
}

void	right_redir(char **command, char **envp, char *file, int mode)
{
	int	fd;
	int	fpid;

	if (mode == 0)
		fd = open(ft_strtrim(file, " "), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(ft_strtrim(file, " "), O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error");
		return ;
	}
	fpid = fork();
	if (fpid == 0)
		cuta_the_second(command, envp, fd);
	else
		waitpid(fpid, NULL, 0);
}

void	left_redir(char **command, char **envp, char *file)
{
	int	fd;
	int	fpid;

	fd = open(ft_strtrim(file, " "), O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return ;
	}
	fpid = fork();
	if (fpid == 0)
		cuta_the_first(command, envp, fd);
	else
		waitpid(fpid, NULL, 0);
}
