/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:49:03 by pgaspar           #+#    #+#             */
/*   Updated: 2024/12/02 19:19:32 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	here_doc(char *delimiter);
void	cuta(char **command, char **envp);
void	forka(char **command, char **envp);
void	pipe_it(char **command, char **envp);
void	just_execute(char **command, char **envp);
void	cuta_the_second(char **command, char **envp, int fd);
void	cuta_in_between(char **command, char **envp, int *pipe_fd);
void	cuta_the_first(char **command, char **envp, int *pipe_fd, int fd);

char	*get_caminho(char **path_copy, char **command);

#endif
