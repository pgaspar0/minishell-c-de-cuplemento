/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:01:11 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/09 16:15:09 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
//# include "pipex.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_redirection
{
	char					*file;
	int						type;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command
{
	char					**args;
	t_redirection			*redirs;
	struct s_command		*next;
}							t_command;

t_env						*init_env(char **envp);
t_command					*parse_commands(char **tokens);

bool						validate_syntax(char **tokens);
bool						is_special_char(char c);

int							open_file(const char *filename, int flags,
								int mode);
int							is_valid_identifier(char *key);
int							is_builtin_command(char **args);
int							here_doc(char *delimiter, int original_stdout_fd);

void						handle_redirections(t_redirection *redirs,
								int original_stdout_fd);
void						free_redirections(t_redirection *redir);
void						free_commands(t_command *cmd);
void						skip_quotes(const char *input, size_t *index,
								char quote);
void						ft_env(t_env *env);
void						ft_export(t_env **env, char *var);
void						update_env(t_env **env, char *key, char *value);
void						execute_commands(t_command *cmd_list, char **envp);
void						execute_commands_iterative(t_command *cmd_list,
								char **envp);

char						*get_caminho(char **path_copy, char **command);
char						*mat_concat(char **mat);
char						**ft_parse(const char *s);
char						**ft_parse2(const char *s);
char						**tokenize(const char *input);

#endif
