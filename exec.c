/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:47:49 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/14 12:24:49 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands_iterative(t_command *cmd_list, t_env **envs)
{
	char		**env_matrix;
	int			pipe_fd[2];
	pid_t		pid;
	t_command	*current;
	int			in_fd;

	in_fd = 0;
	current = cmd_list;
	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1)
		{
			perror("Pipe error");
			exit(1);
		}
		if (is_builtin_command(current->args) && !current->next)
		{
			execute_builtin(current->args, envs);
		}
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("Fork error");
				exit(1);
			}
			if (pid == 0)
			{
				if (in_fd != 0)
				{
					dup2(in_fd, 0);
					close(in_fd);
				}
				if (current->next)
				{
					dup2(pipe_fd[1], 1);
					close(pipe_fd[0]);
					close(pipe_fd[1]);
				}
				handle_redirections(current->redirs, STDOUT_FILENO);
				if (is_builtin_command(current->args))
				{
					execute_builtin(current->args, envs);
					exit(0);
				}
				else
				{
					env_matrix = env_to_matrix(*envs);
					execve(get_caminho(ft_split(getenv("PATH"), ':'),
							current->args), current->args, env_matrix);
					perror("Execve error");
					free_matrix(env_matrix);
					exit(1);
				}
			}
			else
			{
				waitpid(pid, NULL, 0);
				if (in_fd != 0)
					close(in_fd);
				if (current->next)
				{
					close(pipe_fd[1]);
					in_fd = pipe_fd[0];
				}
			}
		}
		current = current->next;
	}
}
