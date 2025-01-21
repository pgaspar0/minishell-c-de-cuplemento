/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:33:59 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/21 09:58:26 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *delimiter, int original_stdout_fd)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	rl_outstream = fopen("/dev/tty", "w");
	if (!rl_outstream)
	{
		perror("Error opening /dev/tty");
		exit(1);
	}
	(void)original_stdout_fd;
	line = readline("heredoc> ");
	while (line && ft_strncmp(delimiter, line, ft_strlen(delimiter)))
	{
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putchar_fd('\n', pipe_fd[1]);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

// separate the if statements into a function

void	redir_type(t_redirection *redir, int *fd, int original_stdout_fd)
{
	if (redir->type == 0)
	{
		*fd = open_file(redir->file, O_RDONLY, 0);
		dup2(*fd, 0);
	}
	else if (redir->type == 1)
	{
		*fd = open_file(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(*fd, 1);
	}
	else if (redir->type == 2)
	{
		*fd = open_file(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(*fd, 1);
	}
	else if (redir->type == 3)
	{
		*fd = here_doc(redir->file, original_stdout_fd);
		dup2(*fd, 0);
	}
}

void	handle_redirections(t_redirection *redirs, int original_stdout_fd)
{
	int				fd;
	t_redirection	*redir;

	redir = redirs;
	while (redir)
	{
		redir_type(redir, &fd, original_stdout_fd);
		close(fd);
		redir = redir->next;
	}
}
