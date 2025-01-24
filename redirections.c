/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:33:59 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/24 15:34:10 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *delimiter, t_shell *shell)
{
	int		saved_stdout;
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	saved_stdout = dup(STDOUT_FILENO);
	dup2(shell->original_stdout_fd, STDOUT_FILENO);
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
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (pipe_fd[0]);
}

void	redir_type(t_redirection *redir, int *fd, t_shell *shell)
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
		*fd = here_doc(redir->file, shell);
		dup2(*fd, 0);
	}
}

void	handle_redirections(t_redirection *redirs, t_shell *shell)
{
	int				fd;
	t_redirection	*redir;

	redir = redirs;
	while (redir)
	{
		redir_type(redir, &fd, shell);
		close(fd);
		redir = redir->next;
	}
}
