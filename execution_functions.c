/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:28:31 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/09 16:15:23 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_command *cmd_list, char **envp)
{
	if (!cmd_list)
		return ;
	// int original_stdout_fd = dup(STDOUT_FILENO);
	// execute_single_command(cmd_list, envp, 0, 1, original_stdout_fd);
	execute_commands_iterative(cmd_list, envp);
}
void	execute_commands_iterative(t_command *cmd_list, char **envp)
{
	int pipe_fd[2];
	pid_t pid;
	t_command *current;

	int in_fd = 0; // Entrada inicial: STDIN
	current = cmd_list;
	while (current)
	{
		// Criação de pipe, se necessário
		if (current->next && pipe(pipe_fd) == -1)
		{
			perror("Pipe error");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Fork error");
			exit(1);
		}
		if (pid == 0)
		{ // Processo filho
			if (in_fd != 0)
			{ // Redirecionar entrada, se necessário
				dup2(in_fd, 0);
				close(in_fd);
			}
			if (current->next)
			{ // Redirecionar saída para o próximo comando
				dup2(pipe_fd[1], 1);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			handle_redirections(current->redirs, STDOUT_FILENO);
			if (is_builtin_command(current->args))
			{
				exit(0);
			}
			else
			{
				execve(get_caminho(ft_split(getenv("PATH"), ':'), current->args),
				current->args, envp);
				perror("Execve error");
				exit(1);
			}
		}
		else
		{ // Processo pai
			waitpid(pid, NULL, 0);
			if (in_fd != 0) // Fechar entrada antiga
				close(in_fd);
			if (current->next)
			{ // Configurar entrada para o próximo comando
				close(pipe_fd[1]);
				in_fd = pipe_fd[0];
			}
		}
		current = current->next; // Avançar para o próximo comando
	}
}
