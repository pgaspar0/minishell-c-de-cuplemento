/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:28:31 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/14 12:00:40 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_command *cmd_list, t_env **envs, int *g_status)
{
	if (!cmd_list)
		return ;
	// int original_stdout_fd = dup(STDOUT_FILENO);
	// execute_single_command(cmd_list, envp, 0, 1, original_stdout_fd);
	execute_commands_iterative(cmd_list, envs, g_status);
}
/* void	execute_commands_iterative(t_command *cmd_list, t_env **envs)
{
	char **env_matrix;
	int pipe_fd[2];
	pid_t pid;
	t_command *current;

	int in_fd = 0;
	current = cmd_list;
	while (current)
	{
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
				execve(get_caminho(ft_split(getenv("PATH"), ':'), current->args),
				current->args, env_matrix);
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
		current = current->next;
	}
} */

/* void execute_commands_iterative(t_command *cmd_list, t_env **envs)
{
    char **env_matrix;
    int pipe_fd[2];
    int in_fd = STDIN_FILENO;
    t_command *current = cmd_list;

    while (current)
    {
        if (current->next && pipe(pipe_fd) == -1)
        {
            perror("Pipe error");
            exit(1);
        }

        if (is_builtin_command(current->args))
        {
            int saved_stdin = dup(STDIN_FILENO);
            int saved_stdout = dup(STDOUT_FILENO);

            if (in_fd != STDIN_FILENO)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (current->next)
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            handle_redirections(current->redirs, STDOUT_FILENO);
            execute_builtin(current->args, envs);

            dup2(saved_stdin, STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
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
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("Fork error");
                exit(1);
            }
            if (pid == 0)
            {
                if (in_fd != STDIN_FILENO)
                {
                    dup2(in_fd, STDIN_FILENO);
                    close(in_fd);
                }
                if (current->next)
                {
                    dup2(pipe_fd[1], STDOUT_FILENO);
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
            {
                waitpid(pid, NULL, 0);
            }
        }

        if (in_fd != STDIN_FILENO)
            close(in_fd);
        if (current->next)
        {
            close(pipe_fd[1]);
            in_fd = pipe_fd[0];
        }

        current = current->next;
    }
} */

/* void execute_commands_iterative(t_command *cmd_list, t_env **envs)
{
    char        **env_matrix;
    int         pipe_fd[2];
    pid_t       pid;
    t_command   *current;
    int         in_fd = STDIN_FILENO;

    current = cmd_list;
    while (current)
    {
        // Cria um pipe se houver um próximo comando
        if (current->next && pipe(pipe_fd) == -1)
        {
            perror("Pipe error");
            exit(EXIT_FAILURE);
        }

        // Se o comando for uma builtin
        if (is_builtin_command(current->args))
        {
            // Redireciona entrada, se necessário
            if (in_fd != STDIN_FILENO)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            // Redireciona saída para o próximo pipe, se necessário
            if (current->next)
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
                close(pipe_fd[0]);
            }

            // Executa a builtin e continua para o próximo comando
            execute_builtin(current->args, envs);
        }
        else
        {
            // Processo externo: Cria fork
            pid = fork();
            if (pid == -1)
            {
                perror("Fork error");
                exit(EXIT_FAILURE);
            }
            if (pid == 0) // Processo filho
            {
                // Redireciona entrada, se necessário
                if (in_fd != STDIN_FILENO)
                {
                    dup2(in_fd, STDIN_FILENO);
                    close(in_fd);
                }

                // Redireciona saída para o próximo pipe, se necessário
                if (current->next)
                {
                    dup2(pipe_fd[1], STDOUT_FILENO);
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);
                }

                // Executa o comando externo
                env_matrix = env_to_matrix(*envs);
                execve(get_caminho(ft_split(getenv("PATH"), ':'), current->args), current->args, env_matrix);
                perror("Execve error");
                free_matrix(env_matrix);
                exit(EXIT_FAILURE);
            }
            else // Processo pai
            {
                waitpid(pid, NULL, 0);
            }
        }

        // Atualiza o in_fd para o próximo comando
        if (in_fd != STDIN_FILENO)
            close(in_fd);
        if (current->next)
        {
            close(pipe_fd[1]); // Fecha o lado de escrita do pipe
            in_fd = pipe_fd[0]; // Lado de leitura para o próximo comando
        }

        current = current->next; // Vai para o próximo comando
    }
} */

void execute_commands_iterative(t_command *cmd_list, t_env **envs, int *g_status)
{
    char        **env_matrix;
    int         pipe_fd[2];
    pid_t       pid;
    int     status;
    t_command   *current;

    int in_fd = 0;
    current = cmd_list;
    while (current)
    {
        // Cria um pipe se houver mais comandos após o atual
        if (current->next && pipe(pipe_fd) == -1)
        {
            perror("Pipe error");
            exit(1);
        }

        // Caso o comando seja o último e seja uma builtin, executa no processo pai
        if (!current->next && is_builtin_command(current->args))
        {
            if (in_fd != 0) // Redireciona entrada, se necessário
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            handle_redirections(current->redirs, STDOUT_FILENO); // Lida com redirecionamentos
            execute_builtin(current->args, envs); // Executa a builtin diretamente
            break; // Sai do loop após executar o último comando
        }

        // Cria um processo filho para outros casos
        pid = fork();
        if (pid == -1)
        {
            perror("Fork error");
            exit(1);
        }

        if (pid == 0) // Processo filho
        {
            if (in_fd != 0) // Redireciona entrada, se necessário
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (current->next) // Redireciona saída para o próximo pipe
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            handle_redirections(current->redirs, STDOUT_FILENO); // Lida com redirecionamentos
            if (is_builtin_command(current->args))
            {
                execute_builtin(current->args, envs); // Executa builtin
                exit(0); // Sai do processo filho
            }
            else
            {
                env_matrix = env_to_matrix(*envs); // Transforma envs para matriz
                execve(get_caminho(ft_split(getenv("PATH"), ':'), current->args), current->args, env_matrix);
                perror("Execve error");
                free_matrix(env_matrix);
                exit(1);
            }
        }
        else // Processo pai
        {
            waitpid(pid, &status, 0); // Espera o processo filho terminar
            update_status(envs, status, g_status);
            if (in_fd != 0) // Fecha o lado de leitura do pipe anterior
                close(in_fd);
            if (current->next) // Atualiza o in_fd para o próximo comando
            {
                close(pipe_fd[1]); // Fecha o lado de escrita do pipe atual
                in_fd = pipe_fd[0]; // Atualiza para o lado de leitura
            }
        }

        current = current->next; // Avança para o próximo comando
    }
}


