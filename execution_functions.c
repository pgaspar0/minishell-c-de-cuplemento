/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:28:31 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/21 09:30:36 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_shell *shell)
{
	if (!shell->commands)
		return ;
	execute_commands_iterative(shell);
}

void	case_builtin_alone(t_command *current, t_env **envs)
{
	int	ret;
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	handle_redirections(current->redirs, STDOUT_FILENO);
	ret = execute_builtin(current->args, envs);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	update_exit_status(envs, g_status_changer(ret));
}

void	execute_child(t_command *current, int *pipe_fd, int *in_fd, t_shell *shell)
{
	if (*in_fd != 0)
	{
		dup2(*in_fd, 0);
		close(*in_fd);
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
		shell->ret = execute_builtin(current->args, &shell->envs);
		exit(shell->ret);
	}
	else
	{
		shell->env_matrix = env_to_matrix(shell->envs);
		cuta(current->args, shell->env_matrix);
		free_matrix(shell->env_matrix);
		exit(0);
	}
}

void	fork_and_execute(t_command *current, int *pipe_fd, int *in_fd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	g_int(1);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		exit(1);
	}
	if (pid == 0)
		execute_child(current, pipe_fd, in_fd, shell);
	else
	{
		waitpid(pid, &status, 0);
		update_exit_status(&shell->envs, status);
		if (*in_fd != 0)
			close(*in_fd);
		if (current->next)
		{
			close(pipe_fd[1]);
			*in_fd = pipe_fd[0];
		}
	}
	g_int(0);
}

void	execute_commands_iterative(t_shell *shell)
{
	int			in_fd;
	t_command	*current;
	int			pipe_fd[2];

	in_fd = 0;
	current = shell->commands;
	if (is_builtin_command(current->args) && !current->next)
	{
		case_builtin_alone(current, &shell->envs);
		return ;
	}
	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1)
		{
			perror("Pipe error");
			exit(1);
		}
		fork_and_execute(current, pipe_fd, &in_fd, shell);
		current = current->next;
	}
}
