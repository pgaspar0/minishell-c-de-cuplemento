/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hfuncs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:05:09 by pgaspar           #+#    #+#             */
/*   Updated: 2024/12/02 11:37:12 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// implementa a logica principal e deixa o output do penultimo comando na stdin
void	forka(char **command, char **envp)
{
	int	fpid;
	// int	pipe_fd[2];

	/* if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		return ;
	} */
	fpid = fork();
	if (fpid == 0)
		cuta(command, envp);
	else
	{
		/* dup2(pipe_fd[0], 0);
		close(pipe_fd[1]); */
		waitpid(fpid, NULL, 0);
	}
}

// pega o caminho do executavel
char	*get_caminho(char **path_copy, char **command)
{
	int		i;
	int		status;
	char	*temp;
	char	*caminho;

	i = 0;
	while (path_copy[i])
	{
		temp = ft_strjoin(path_copy[i], "/");
		caminho = ft_strjoin(temp, command[0]);
		free(temp);
		status = access(caminho, X_OK | F_OK);
		if (status == 0)
			return (caminho);
		free(caminho);
		i++;
	}
	return (NULL);
}

// redireciona de uma lado da pipe para outro de formas a cada
// processo transferir a informação um para o outro
void	cuta_in_between(char **command, char **envp, int *pipe_fd)
{
	char	*caminho;
	char	*path;
	char	**path_copy;

	path = getenv("PATH");
	path_copy = ft_split(path, ':');
	caminho = get_caminho(path_copy, command);
	if (!caminho)
	{
		perror("\033[1;31mError\033[0m");
		free_matrix(path_copy);
		return ;
	}
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	execve(caminho, command, envp);
}

// redireciona o resultado do ultimo comando para o ficheiro de destino
void	cuta_the_second(char **command, char **envp, int fd)
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
		return ;
	}
	dup2(fd, 1);
	close(fd);
	execve(caminho, command, envp);
}

//executa o comando pegando como input o ficheiro do fd e manda o output para um lado da pipe
void	cuta_the_first(char **command, char **envp, int *pipe_fd, int fd)
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
		free_matrix(command);
		exit(1);
	}
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(caminho, command, envp);
}
