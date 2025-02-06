/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:33:59 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/06 07:06:21 by gamekiller2      ###   ########.fr       */
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
	line = ft_expansion(readline("heredoc> "), shell->envs, 1);
	while (line && ft_strncmp(delimiter, line, ft_strlen(delimiter)))
	{
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putchar_fd('\n', pipe_fd[1]);
		free(line);
		line = ft_expansion(readline("heredoc> "), shell->envs, 1);
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
		signal(SIGINT, SIG_DFL);
		*fd = here_doc(redir->file, shell);
		signal(SIGINT, handle_sigint);
		dup2(*fd, 0);
	}
}

void	handle_redirections(t_shell *shell)
{
	int				fd;
	t_redirection	*redir;

	redir = shell->current->redirs;
	while (redir)
	{
		redir_type(redir, &fd, shell);
		close(fd);
		redir = redir->next;
	}
}
