/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:00:27 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/16 18:53:30 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

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
	t_env		*envs;
	char		*input;
	char		**tokens;
	t_command	*commands;

	envs = init_env(envp);
	update_env(&envs, "?", "0");
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		add_history(input);
		tokens = tokenize(input, envs);
		if (!validate_syntax(tokens))
		{
			printf("Syntax error\n");
			free_matrix(tokens);
			free(input);
			continue ;
		}
		commands = parse_commands(tokens);
		free_matrix(tokens);
		execute_commands(commands, &envs);
		free_commands(commands);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	signal(3, SIG_IGN);
	signal(SIGINT, handle_sigint);
	shell_loop(envp);
	return (0);
}
