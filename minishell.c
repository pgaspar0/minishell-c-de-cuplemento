/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:00:27 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/08 16:40:25 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error_things(t_shell *shell)
{
	printf("Syntax error\n");
	update_env(&shell->envs, "?", "2", 2);
	free_matrix(shell->tokens);
	free(shell->input);
}

void	shell_loop(char **envp)
{
	t_shell	shell;

	shell.original_stdout_fd = dup(STDOUT_FILENO);
	shell.envs = init_env(envp);
	update_env(&shell.envs, "?", "0", 2);
	while (1)
	{
		shell.input = readline("beshe> ");
		if (!shell.input)
			break ;
		add_history(shell.input);
		if (g_status_changer(-1) == 130)
			update_exit_status(&shell.envs, g_status_changer(-1));
		shell.tokens = tokenize(&shell);
		if (!validate_syntax(shell.tokens) || shell.tokens == NULL)
		{
			syntax_error_things(&shell);
			continue ;
		}
		shell.commands = parse_commands(shell.tokens);
		free_matrix(shell.tokens);
		execute_commands(&shell);
	}
	free_envs(shell.envs);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	shell_loop(envp);
	rl_clear_history();
	return (g_status_changer(-1));
}
