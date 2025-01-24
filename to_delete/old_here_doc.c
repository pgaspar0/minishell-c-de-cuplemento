/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:35:16 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/24 15:35:22 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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