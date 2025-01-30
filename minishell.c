/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:00:27 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/28 16:08:12 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_status_changer(130);
	write(1, "\n", 1);
	rl_on_new_line();
	if (g_int(-1) == 0)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	shell_loop(char **envp)
{
	t_shell		shell;

	shell.original_stdout_fd = dup(STDOUT_FILENO);
	shell.envs = init_env(envp);
	update_env(&shell.envs, "?", "0", 2);
	while (1)
	{
		shell.input = readline("beshe> ");
		if (!shell.input)
			break ;
		add_history(shell.input);
		shell.tokens = tokenize(&shell);
		if (!validate_syntax(shell.tokens))
		{
			printf("Syntax error\n");
			free_matrix(shell.tokens);
			free(shell.input);
			continue ;
		}
		shell.commands = parse_commands(shell.tokens);
		free_matrix(shell.tokens);
		execute_commands(&shell);
		free_commands(shell.commands);
		free(shell.input);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	shell_loop(envp);
	return (0);
}
