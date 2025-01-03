/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:05:25 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/03 04:00:48 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int 						here_doc(char *delimiter, int original_stdout_fd);
int							open_file(const char *filename, int flags,
								int mode);
void						execute_single_command(t_command *cmd, char **envp,
								int in_fd, int out_fd, int original_stdout_fd);
void                        execute_commands_iterative(t_command *cmd_list, char **envp);
t_command					*parse_commands(char **tokens);
void                        handle_redirections(t_redirection *redirs, int original_stdout_fd);
void						shell_loop(char **envp);
void						execute_commands(t_command *cmd_list, char **envp);
void						free_redirections(t_redirection *redir);
void						free_commands(t_command *cmd);
void						skip_quotes(const char *input, size_t *index, char quote);
bool						is_special_char(char c);
bool						validate_syntax(char **tokens);
char						*get_caminho(char **path_copy, char **command);
char						**tokenize(const char *input);

// int here_doc(char *delimiter, int original_stdout_fd)
// {
// 	int		pipe_fd[2];
// 	char	*line;

// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("Error");
// 		exit(1);
// 	}

//     /* rl_outstream = fopen("/dev/tty", "w");
//     if (!rl_outstream) {
//         perror("Error opening /dev/tty");
//         exit(1);
//     } */
// 	// line = readline("heredoc> ");
//     ft_putstr_fd("Estou aqui antes do primeiro heredoc\n", original_stdout_fd);
//     ft_putstr_fd("heredoc> ", original_stdout_fd);
//     ft_putstr_fd("Estou aqui antes do pedido\n", original_stdout_fd);
//     line = ft_strtrim(get_next_line(0), "\n");
//     ft_putstr_fd("Estou aqui antes do loop\n", original_stdout_fd);
// 	while (line && ft_strncmp(delimiter, line, ft_strlen(delimiter)))
// 	{
// 		ft_putstr_fd(line, pipe_fd[1]);
// 		ft_putchar_fd('\n', pipe_fd[1]);
// 		free(line);
// 		// line = readline("heredoc> ");
//         ft_putstr_fd("heredoc> ", original_stdout_fd);
//         line = ft_strtrim(get_next_line(0), "\n");
// 	}
// 	free(line);
// 	close(pipe_fd[1]);
// 	return (pipe_fd[0]);
// }

int here_doc(char *delimiter, int original_stdout_fd)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
    rl_outstream = fopen("/dev/tty", "w");
    if (!rl_outstream) {
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

char	*get_caminho(char **path_copy, char **command)
{
	int		i;
	int		status;
	char	*temp;
	char	*caminho;

	i = 0;
	while (path_copy[i])
	{
		temp = ft_strjoin(path_copy[i], "/");
		caminho = ft_strjoin(temp, command[0]);
		free(temp);
		status = access(caminho, X_OK | F_OK);
		if (status == 0)
			return (caminho);
		free(caminho);
		i++;
	}
	return (NULL);
}

bool	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void skip_quotes(const char *input, size_t *index, char quote)
{
    (*index)++;
    while (input[*index] && input[*index] != quote)
        (*index)++;
    if (input[*index] == quote)
        (*index)++;
}

char **tokenize(const char *input)
{
    char        **tokens;
    size_t      token_count;
    size_t      start;
    size_t      i;
    bool        quoted;

    tokens = malloc(sizeof(char *) * 1024);
    if (!tokens)
        return NULL;
    token_count = 0;
    i = 0;
    while (input[i])
    {
        while (input[i] && ft_isspace(input[i]))
            i++;
        if (input[i] == '\0')
            break;
        start = i;
        quoted = (input[i] == '\'' || input[i] == '"');
        if (quoted)
        {
            skip_quotes(input, &i, input[i]);
            tokens[token_count++] = ft_substr(input, start + 1, i - start - 2);
        }
        else if (is_special_char(input[i]))
        {
            i++;
            if ((input[start] == '<' || input[start] == '>') && input[i] == input[start])
                i++;
            tokens[token_count++] = ft_substr(input, start, i - start);
        }
        else
        {
            while (input[i] && !ft_isspace(input[i]) && !is_special_char(input[i]))
                i++;
            tokens[token_count++] = ft_substr(input, start, i - start);
        }
    }
    tokens[token_count] = NULL;
    return tokens;
}

bool	validate_syntax(char **tokens)
{
	for (int i = 0; tokens[i]; i++)
	{
		if (is_special_char(tokens[i][0]))
		{
			if (tokens[i][1] != '\0' && (tokens[i][0] != '<'
					&& tokens[i][0] != '>'))
				return (false);
			if (i == 0 || !tokens[i + 1] || is_special_char(tokens[i + 1][0]))
				return (false);
		}
	}
	return (true);
}

/* t_command	*parse_commands(char **tokens)
{
	t_command		*head;
	t_command		*current;
	t_redirection	*redir;
	size_t			arg_count;

	head = NULL;
	current = NULL;
	for (int i = 0; tokens[i];)
	{
		if (!current)
		{
			current = malloc(sizeof(t_command));
			current->args = malloc(sizeof(char *) * 1024);
			current->redirs = NULL;
			current->next = NULL;
			if (!head)
				head = current;
		}
		arg_count = 0;
		while (tokens[i] && tokens[i][0] != '|')
		{
			if (tokens[i][0] == '<' || tokens[i][0] == '>')
			{
				redir = malloc(sizeof(t_redirection));
				redir->type = (tokens[i][0] == '>') + (tokens[i][1] == '>');
                if (tokens[i][0] == '<' && tokens[i][1] == '<')
                    redir->type = 3;
				redir->file = ft_strdup(tokens[++i]);
				redir->next = current->redirs;
				current->redirs = redir;
			}
			else
			{
				current->args[arg_count++] = ft_strdup(tokens[i]);
			}
			i++;
		}
		current->args[arg_count] = NULL;
		if (tokens[i] && tokens[i][0] == '|')
		{
            current->next = malloc(sizeof(t_command));
			if (!current->next)
				return (NULL);
			current = current->next;
			current->args = malloc(sizeof(char *) * 1024);
			if (!current->args)
				return (NULL);
			current->redirs = NULL;
			current->next = NULL;
			i++;
		}
	}
	return (head);
} */

t_command	*parse_commands(char **tokens)
{
	t_command		*head;
	t_command		*current;
	t_redirection	*redir;
	t_redirection	*last_redir; // Ponteiro para o último redirecionamento
	size_t			arg_count;

	head = NULL;
	current = NULL;
	for (int i = 0; tokens[i];)
	{
		if (!current)
		{
			current = malloc(sizeof(t_command));
			current->args = malloc(sizeof(char *) * 1024);
			current->redirs = NULL;
			last_redir = NULL; // Inicialize como NULL
			current->next = NULL;
			if (!head)
				head = current;
		}
		arg_count = 0;
		while (tokens[i] && tokens[i][0] != '|')
		{
			if (tokens[i][0] == '<' || tokens[i][0] == '>')
			{
				redir = malloc(sizeof(t_redirection));
				redir->type = (tokens[i][0] == '>') + (tokens[i][1] == '>');
                if (tokens[i][0] == '<' && tokens[i][1] == '<')
                    redir->type = 3;
				redir->file = ft_strdup(tokens[++i]);
				redir->next = NULL;

				// Adicione ao final usando last_redir
				if (!last_redir)
					current->redirs = redir; // Primeiro redirecionamento
				else
					last_redir->next = redir; // Próximo redirecionamento
				last_redir = redir; // Atualize o ponteiro para o último redirecionamento
			}
			else
			{
				current->args[arg_count++] = ft_strdup(tokens[i]);
			}
			i++;
		}
		current->args[arg_count] = NULL;
		if (tokens[i] && tokens[i][0] == '|')
		{
            current->next = malloc(sizeof(t_command));
			if (!current->next)
				return (NULL);
			current = current->next;
			current->args = malloc(sizeof(char *) * 1024);
			if (!current->args)
				return (NULL);
			current->redirs = NULL;
			last_redir = NULL; // Redefina para o novo comando
			current->next = NULL;
			i++;
		}
	}
	return (head);
}


void	shell_loop(char **envp)
{
	char *input;
    char **tokens;
    t_command *commands;

    while (1) 
    {
        input = readline("minishell> ");
        if (!input) {
            printf("Exiting minishell...\n");
            break;
        }

        add_history(input);
        tokens = tokenize(input);
        if (!validate_syntax(tokens)) {
            printf("Syntax error\n");
            free_matrix(tokens);
            free(input);
            continue;
        }
        commands = parse_commands(tokens);
        free_matrix(tokens);
        execute_commands(commands, envp);
        free_commands(commands);
        free(input);
    }
}

int	open_file(const char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	return (fd);
}

void handle_redirections(t_redirection *redirs, int original_stdout_fd)
{
    for (t_redirection *redir = redirs; redir; redir = redir->next) {
        int fd;
        if (redir->type == 0) {
            fd = open_file(redir->file, O_RDONLY, 0);
            dup2(fd, 0);
        } else if (redir->type == 1) {
            fd = open_file(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, 1);
        } else if (redir->type == 2) {
            fd = open_file(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, 1);
        } else if (redir->type == 3) {
            fd = here_doc(redir->file, original_stdout_fd);
            dup2(fd, 0);
        }
        close(fd);
    }
}

/* void execute_single_command(t_command *cmd, char **envp, int in_fd, int out_fd, int original_stdout_fd) {
    int pipe_fd[2];
    pid_t pid;

    if (cmd->next && pipe(pipe_fd) == -1) {
        perror("Pipe error");
        exit(1);
    }
    pid = fork();
    if (pid == -1) {
        perror("Fork error");
        exit(1);
    }

    if (pid == 0) {
        if (in_fd != 0) {
            dup2(in_fd, 0);
            close(in_fd);
        }
        if (cmd->next) {
            dup2(pipe_fd[1], 1);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
        } else if (out_fd != 1) {
            dup2(out_fd, 1);
            close(out_fd);
        }
        handle_redirections(cmd->redirs, original_stdout_fd);
        execve(get_caminho(ft_split(getenv("PATH"), ':'), cmd->args), cmd->args, envp);
        perror("Execve error");
        exit(1);
    } else {
        if (in_fd != 0)
            close(in_fd);
        if (cmd->next) {
            close(pipe_fd[1]);
            execute_single_command(cmd->next, envp, pipe_fd[0], out_fd, original_stdout_fd);
        } else if (out_fd != 1) {
            close(out_fd);
        }
        waitpid(pid, NULL, 0);
    }
} */

void execute_commands_iterative(t_command *cmd_list, char **envp)
{
    int pipe_fd[2];
    int in_fd = 0;  // Entrada inicial: STDIN
    pid_t pid;
    t_command *current = cmd_list;

    while (current) {
        // Criação de pipe, se necessário
        if (current->next && pipe(pipe_fd) == -1) {
            perror("Pipe error");
            exit(1);
        }

        pid = fork();
        if (pid == -1) {
            perror("Fork error");
            exit(1);
        }

        if (pid == 0) { // Processo filho
            if (in_fd != 0) { // Redirecionar entrada, se necessário
                dup2(in_fd, 0);
                close(in_fd);
            }
            if (current->next) { // Redirecionar saída para o próximo comando
                dup2(pipe_fd[1], 1);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            handle_redirections(current->redirs, STDOUT_FILENO);
            execve(get_caminho(ft_split(getenv("PATH"), ':'), current->args), current->args, envp);
            perror("Execve error");
            exit(1);
        } else { // Processo pai
            waitpid(pid, NULL, 0);
            if (in_fd != 0) // Fechar entrada antiga
                close(in_fd);
            if (current->next) { // Configurar entrada para o próximo comando
                close(pipe_fd[1]);
                in_fd = pipe_fd[0];
            }
        }
        current = current->next; // Avançar para o próximo comando
    }
}


void	execute_commands(t_command *cmd_list, char **envp)
{
	if (!cmd_list)
		return ;
    // int original_stdout_fd = dup(STDOUT_FILENO);
	// execute_single_command(cmd_list, envp, 0, 1, original_stdout_fd);
    execute_commands_iterative(cmd_list, envp);
}

void	free_redirections(t_redirection *redir)
{
	t_redirection	*temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		free(temp->file);
		free(temp);
	}
}

void	free_commands(t_command *cmd)
{
	t_command	*temp;

	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		free_matrix(temp->args);
		free_redirections(temp->redirs);
		free(temp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	shell_loop(envp);
	return (0);
}
