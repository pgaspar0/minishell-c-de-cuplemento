/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:05:25 by pgaspar           #+#    #+#             */
/*   Updated: 2024/12/11 19:10:48 by pgaspar          ###   ########.fr       */
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


int							open_file(const char *filename, int flags,
								int mode);
void						execute_single_command(t_command *cmd, char **envp,
								int in_fd, int out_fd);
t_command					*parse_commands(char **tokens);
void						shell_loop(char **envp);
void						execute_commands(t_command *cmd_list, char **envp);
void						free_redirections(t_redirection *redir);
void						free_commands(t_command *cmd);
void						here_doc(char *delimiter);
void						skip_quotes(const char *input, size_t *index, char quote);
bool						is_special_char(char c);
bool						validate_syntax(char **tokens);
char						*get_caminho(char **path_copy, char **command);
char						**tokenize(const char *input);

void	here_doc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	line = readline("heredoc> ");
	while (ft_strncmp(delimiter, line, ft_strlen(delimiter)))
	{
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putchar_fd('\n', pipe_fd[1]);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
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

    tokens = malloc(sizeof(char *) * 1024); // Adjust size as needed
    if (!tokens)
        return (NULL);
    token_count = 0;
    i = 0;
    while (input[i])
    {
        while (input[i] && ft_isspace(input[i])) // Skip whitespace
            i++;
        if (input[i] == '\0')
            break;
        start = i;
        if (input[i] == '\'' || input[i] == '"')
        {
            skip_quotes(input, &i, input[i]);
        }
        else if (is_special_char(input[i]))
        {
            i++;
            if ((input[start] == '<' || input[start] == '>') && input[i] == input[start])
                i++; // Handle << or >>
        }
        else
        {
            while (input[i] && !ft_isspace(input[i]) && !is_special_char(input[i]))
                i++;
        }
		// printf("Token: %s\n", ft_substr(input, start, i - start));
        tokens[token_count++] = ft_substr(input, start, i - start);
    }
    tokens[token_count] = NULL;
    return (tokens);
}

bool	validate_syntax(char **tokens)
{
	for (int i = 0; tokens[i]; i++)
	{
		if (is_special_char(tokens[i][0]))
		{
			if (tokens[i][1] != '\0' && (tokens[i][0] != '<'
					&& tokens[i][0] != '>'))
				return (false); // Invalid special token
			if (i == 0 || !tokens[i + 1] || is_special_char(tokens[i + 1][0]))
				return (false); // Misplaced special token
		}
	}
	return (true);
}

t_command	*parse_commands(char **tokens)
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
			current->args = malloc(sizeof(char *) * 1024); // Adjust size
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
			current = current->next;
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

    while (1) {
        input = readline("minishell> ");
        if (!input) {
            printf("Exiting minishell...\n");
            break;
        }

        add_history(input);
        tokens = tokenize(input);
        printf("\n[DEBUG] Tokens:\n");
        for (int i = 0; tokens[i]; i++) {
            printf("  Token %d: %s\n", i, tokens[i]);
        }

        if (!validate_syntax(tokens)) {
            printf("Syntax error\n");
            free_matrix(tokens);
            free(input);
            continue;
        }

        commands = parse_commands(tokens);
        printf("\n[DEBUG] Parsed Commands:\n");
        for (t_command *cmd = commands; cmd; cmd = cmd->next) {
            printf("  Command args: ");
            for (int i = 0; cmd->args[i]; i++) {
                printf("%s ", cmd->args[i]);
            }
            printf("\n  Redirections:\n");
            for (t_redirection *redir = cmd->redirs; redir; redir = redir->next) {
                printf("    Type: %d, File: %s\n", redir->type, redir->file);
            }
        }

        free_matrix(tokens);

        printf("\n[DEBUG] Executing Commands...\n");
        execute_commands(commands, envp);

        printf("\n[DEBUG] Cleaning up...\n");
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

// Execute a single command with redirections and pipes
void	execute_single_command(t_command *cmd, char **envp, int in_fd,
		int out_fd)
{
	int pipe_fd[2];
    pid_t pid;

    if (cmd->next && pipe(pipe_fd) == -1) {
        perror("Pipe error");
        exit(1);
    }

    printf("\n[DEBUG] Forking for command:\n");
    for (int i = 0; cmd->args[i]; i++) {
        printf("  Arg %d: %s\n", i, cmd->args[i]);
    }

    pid = fork();
    if (pid == -1) {
        perror("Fork error");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        if (in_fd != 0) {
            dup2(in_fd, 0);
            close(in_fd);
        }
        if (cmd->next) {
            dup2(pipe_fd[1], 1); // Redirect stdout to pipe
            close(pipe_fd[0]);
            close(pipe_fd[1]);
        } else if (out_fd != 1) {
            dup2(out_fd, 1); // Redirect stdout to output file
            close(out_fd);
        }

        printf("[DEBUG] Applying Redirections...\n");
        for (t_redirection *redir = cmd->redirs; redir; redir = redir->next) {
            int fd;
            if (redir->type == 0) { // Input redirection: <
                fd = open_file(redir->file, O_RDONLY, 0);
                printf("[DEBUG] Redirect input from: %s\n", redir->file);
            } else if (redir->type == 1) { // Output redirection: >
                fd = open_file(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                printf("[DEBUG] Redirect output to: %s\n", redir->file);
            } else if (redir->type == 2) { // Append redirection: >>
                fd = open_file(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                printf("[DEBUG] Append output to: %s\n", redir->file);
            } else if (redir->type == 3) { // Heredoc redirection: <<
                printf("[DEBUG] Starting heredoc with delimiter: %s\n", redir->file);
                here_doc(redir->file);
                continue;
            }
            dup2(fd, (redir->type == 0) ? 0 : 1); // Redirect input or output
            close(fd);
        }

        printf("[DEBUG] Executing command: %s\n", cmd->args[0]);
        execve(get_caminho(ft_split(getenv("PATH"), ':'), cmd->args), cmd->args, envp);
        perror("Execve error");
        exit(1);
    } else {
        // Parent process
        if (in_fd != 0)
            close(in_fd);
        if (cmd->next) {
            close(pipe_fd[1]); // Close write end of pipe
            execute_single_command(cmd->next, envp, pipe_fd[0], out_fd);
        } else if (out_fd != 1) {
            close(out_fd);
        }
        waitpid(pid, NULL, 0);
    }
}

// Main function to execute a list of commands
void	execute_commands(t_command *cmd_list, char **envp)
{
	if (!cmd_list)
		return ;
	execute_single_command(cmd_list, envp, 0, 1);
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
	char		*input;
	char		**tokens;
	t_command	*commands;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{ // Handle EOF (Ctrl-D)
			printf("\nExiting minishell...\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		if (!validate_syntax(tokens))
		{
			fprintf(stderr, "Syntax error\n");
			free_matrix(tokens);
			free(input);
			continue ;
		}
		commands = parse_commands(tokens);
		free_matrix(tokens);
		// Execute parsed commands
		execute_commands(commands, envp);
		// Free memory used for commands
		free_commands(commands);
		free(input);
	}
	return (0);
}
