/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:01:11 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/05 00:10:22 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char					*key;
	char					*value;
	int						flag;
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

typedef struct s_parser
{
	t_command				*head;
	t_command				*current;
	t_redirection			*last_redir;
	t_redirection			*redir;
	size_t					arg_count;
}							t_parser;

typedef struct s_tokenizer
{
	char					*new_input;
	char					**tokens;
	size_t					token_count;
	size_t					start;
	bool					quoted;
}							t_tokenizer;

typedef struct s_shell
{
	int						original_stdout_fd;
	int						exit_status;
	int						ret;
	t_env					*envs;
	char					*input;
	char					**env_matrix;
	char					**tokens;
	t_command				*commands;
	t_command				*current;
}							t_shell;

t_env						*init_env(char **envp);
t_command					*parse_commands(char **tokens);

bool						validate_syntax(char **tokens);
bool						is_special_char(char c);

int							open_file(const char *filename, int flags,
								int mode);
int							is_valid_identifier(char *key);
int							g_int(int n);
int							g_status_changer(int n);
int							is_builtin_command(char **args);
int							here_doc(char *delimiter, t_shell *shell);
int							is_dquotes(const char *input);
int							contains_dollar_sign(const char *input);
int							exit_func(char *exit_code);
int							execute_builtin(t_shell *shell, char **args);
int							is_nbr(const char *str);
int							ft_exit(t_env **env, char **args, char *exit_code,
								t_shell *shell);
int							ft_cd(char **input_path);
int							ft_pwd(void);
int							has_squotes(const char *str);
int							cuta(t_shell *shell);

void						handle_redirections(t_shell *shell);
void						free_redirections(t_redirection *redir);
void						free_commands(t_command *cmd);
void						ft_export_multiple(t_env **env, char **args);
void						ft_unset_multiple(t_env **env, char **args);
void						ft_unset(t_env **env, char *var);
void						ft_echo(char **args);
void						print_error(char *arg);
void						skip_quotes(const char *input, size_t *index,
								char quote);
void						ft_env(t_env *env);
void						handle_sigint(int sig);
void						signal_on_off(int flag);
void						sigquit(int sig);
void						ft_export_no(t_env **env);
void						update_exit_status(t_env **envs, int status);
void						ft_export(t_env **env, char *var);
void						add_new_env(t_env **env, char *key, char *value,
								int flag);
void						update_existing_env(t_env *current, char *value,
								int flag);
void						update_env(t_env **env, char *key, char *value,
								int flag);
void						free_all(t_shell *shell);
void						unset_free(t_env *current);
void						free_envs(t_env *envs);
void						parse_var(char *var, char **key, char **value,
								int *flag);
void						execute_commands(t_shell *t_shell);
void						execute_commands_iterative(t_shell *shell);

char						*get_caminho(char **path_copy, char **command);
char						*ft_getenv(const char *varname, t_env *env_list);
char						*get_caminho(char **path_copy, char **command);
char						*mat_concat(char **mat);
char						**ft_parse(const char *s);
char						**ft_parse2(const char *s);
char						**env_to_matrix(t_env *env_list);
char						**tokenize(t_shell *shell);
char						*ft_expansion(const char *input, t_env *envs,
								int flag);

#endif
