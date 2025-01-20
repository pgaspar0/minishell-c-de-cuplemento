/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:28:31 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/20 07:14:53 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_command *cmd_list, t_env **envs)
{
	if (!cmd_list)
		return ;
	execute_commands_iterative(cmd_list, envs);
}

void	execute_commands_iterative(t_command *cmd_list, t_env **envs)
{
	char		**env_matrix;
	int			pipe_fd[2];
	pid_t		pid;
	t_command	*current;
	int			ret;
	int			status;
	int			saved_stdout;
	int			in_fd;

	in_fd = 0;
	status = 0;
	current = cmd_list;
    if (is_builtin_command(current->args) && !current->next)
	{
		saved_stdout = dup(STDOUT_FILENO);
        handle_redirections(current->redirs, STDOUT_FILENO);
		ret = execute_builtin(current->args, envs);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		update_exit_status(envs, g_status_changer(ret));
        return ;
	}
	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1)
		{
			perror("Pipe error");
			exit(1);
		}
		g_int(1);
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
				ret = execute_builtin(current->args, envs);
				exit(ret);
			}
			else
			{
				env_matrix = env_to_matrix(*envs);
				cuta(current->args, env_matrix);
				free_matrix(env_matrix);
				exit(0);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			update_exit_status(envs, status);
			if (in_fd != 0)
				close(in_fd);
			if (current->next)
			{
				close(pipe_fd[1]);
				in_fd = pipe_fd[0];
			}
		}
		g_int(0);
		current = current->next;
	}
}
