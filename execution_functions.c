/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:28:31 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/08 17:28:22 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_shell *shell)
{
	if (!shell->commands)
		return ;
	shell->status = 0;
	execute_commands_iterative(shell);
	free_commands(shell->commands);
	free(shell->input);
}

void	case_builtin_alone(t_command *current, t_env **envs, t_shell *shell)
{
	int	ret;

	if (handle_redirections(shell) == -1)
	{
		update_env(&shell->envs, "?", "1", 2);
		return ;
	}
	ret = execute_builtin(shell, current->args);
	dup2(shell->original_stdout_fd, STDOUT_FILENO);
	if (ret != 1)
		update_exit_status(envs, g_status_changer(ret));
	else
		update_env(&shell->envs, "?", "1", 2);
}

void	execute_child(int *pipe_fd, int *in_fd, t_shell *shell)
{
	if (*in_fd != 0)
	{
		dup2(*in_fd, 0);
		close(*in_fd);
	}
	if (shell->current->next)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (handle_redirections(shell) == -1)
	{
		free_all(shell);
		exit(1);
	}
	if (is_builtin_command(shell->current->args))
	{
		shell->ret = execute_builtin(shell, shell->current->args);
		free_all(shell);
		exit(shell->ret);
	}
	else
		do_execute(shell);
}

void	fork_and_execute(int *pipe_fd, int *in_fd, t_shell *shell)
{
	pid_t	pid;

	signal_on_off(0);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		exit(1);
	}
	if (pid == 0)
		execute_child(pipe_fd, in_fd, shell);
	else
	{
		waitpid(pid, &shell->status, 0);
		update_exit_status(&shell->envs, shell->status);
		if (*in_fd != 0)
			close(*in_fd);
		if (shell->current->next)
		{
			close(pipe_fd[1]);
			*in_fd = pipe_fd[0];
		}
	}
	signal_on_off(1);
}

void	execute_commands_iterative(t_shell *shell)
{
	int			in_fd;
	int			pipe_fd[2];

	in_fd = 0;
	shell->current = shell->commands;
	if (is_builtin_command(shell->current->args) && !shell->current->next)
	{
		case_builtin_alone(shell->current, &shell->envs, shell);
		return ;
	}
	while (shell->current)
	{
		if (shell->current->next && pipe(pipe_fd) == -1)
		{
			perror("Pipe error");
			exit(1);
		}
		fork_and_execute(pipe_fd, &in_fd, shell);
		shell->current = shell->current->next;
	}
}
