/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:28:31 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/10 20:17:42 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_command *cmd_list, t_env **envs)
{
	if (!cmd_list)
		return ;
	// int original_stdout_fd = dup(STDOUT_FILENO);
	// execute_single_command(cmd_list, envp, 0, 1, original_stdout_fd);
	execute_commands_iterative(cmd_list, envs);
}
/* void	execute_commands_iterative(t_command *cmd_list, t_env **envs)
{
	char **env_matrix;
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
				execute_builtin(current->args, envs);
				exit(0);
			}
			else
			{
				env_matrix = env_to_matrix(*envs);
				execve(get_caminho(ft_split(getenv("PATH"), ':'), current->args),
				current->args, env_matrix);
				perror("Execve error");
				free_matrix(env_matrix);
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
} */
void execute_commands_iterative(t_command *cmd_list, t_env **envs)
{
    char **env_matrix;
    int pipe_fd[2];
    t_command *current;

    int in_fd = 0; // Entrada inicial: STDIN
    current = cmd_list;

    while (current)
    {
        // Criar pipe, se necessário
        if (current->next && pipe(pipe_fd) == -1)
        {
            perror("Pipe error");
            exit(1);
        }

        if (is_builtin_command(current->args))
        {
            // Redirecionar entrada e saída, se necessário
            int saved_stdin = dup(0);
            int saved_stdout = dup(1);

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
            execute_builtin(current->args, envs); // Executa o built-in no processo principal

            // Restaurar descritores originais
            dup2(saved_stdin, 0);
            dup2(saved_stdout, 1);
            close(saved_stdin);
            close(saved_stdout);

            if (current->next)
            {
                close(pipe_fd[1]);
                in_fd = pipe_fd[0];
            }
        }
        else
        {
            // Criar processo filho para comandos externos
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("Fork error");
                exit(1);
            }
            if (pid == 0)
            { // Processo filho
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

                env_matrix = env_to_matrix(*envs);
                execve(get_caminho(ft_split(getenv("PATH"), ':'), current->args),
                       current->args, env_matrix);
                perror("Execve error");
                free_matrix(env_matrix);
                exit(1);
            }
            else
            { // Processo pai
                waitpid(pid, NULL, 0);
            }
        }

        // Gerenciar pipes
        if (in_fd != 0)
            close(in_fd);
        if (current->next && !is_builtin_command(current->args))
        {
            close(pipe_fd[1]);
            in_fd = pipe_fd[0];
        }

        current = current->next;
    }
}
