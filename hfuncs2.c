/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hfuncs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:44:07 by pgaspar           #+#    #+#             */
/*   Updated: 2024/12/04 13:48:46 by pgaspar          ###   ########.fr       */
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
		waitpid(fpid, NULL, 0);
	}
}