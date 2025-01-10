#include "minishell.h"

void execute_commands_iterative(t_command *cmd_list, t_env **envs)
{
    char **env_matrix;
    int pipe_fd[2];
    t_command *current;
    pid_t pid;

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

        // Verificar se é um comando interno (builtin)
        if (is_builtin_command(current->args))
        {
            // Redirecionar entrada e saída no processo principal
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
            execute_builtin(current->args, envs); // Executa diretamente no processo principal

            // Restaurar entrada e saída padrão, se necessário
            if (current->next)
            {
                dup2(0, in_fd);
                dup2(1, STDOUT_FILENO);
            }
        }
        else
        {
            // Comandos externos continuam em um fork
            pid = fork();
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
        if (in_fd != 0) // Fechar entrada antiga
            close(in_fd);
        if (current->next)
        { // Configurar entrada para o próximo comando
            close(pipe_fd[1]);
            in_fd = pipe_fd[0];
        }

        current = current->next; // Avançar para o próximo comando
    }
}
