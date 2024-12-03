/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:00:27 by pgaspar           #+#    #+#             */
/*   Updated: 2024/12/03 13:08:10 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	pipex(char **tokens, char **envp)
{
	char	**command;
	int		saved_stdin;
	int 	saved_stdout;
	int		i;

	i = 0;
	saved_stdin = dup(0);
	saved_stdout = dup(1);
	while (tokens[i])
	{
		if (tokens[i + 1] && tokens[i + 1][0] == '|')
		{
			command = ft_split(tokens[i], ' ');
			pipe_it(command, envp);
			free_matrix(command);
			i++;
		}
		else
		{
    		dup2(saved_stdout, 1);
			command = ft_split(tokens[i], ' ');
			just_execute(command, envp);
			free_matrix(command);
		}
		i++;
	}
	dup2(saved_stdin, 0);
    dup2(saved_stdout, 1);
    close(saved_stdin);
    close(saved_stdout);
}

void	faz_tudo(char *str, char **envp)
{
	char	**tokens;
	char	**final_tokens;
	char	*concat;

	tokens = ft_parse(str);
	concat = mat_concat(tokens);
	final_tokens = ft_parse2(concat);
	pipex(final_tokens, envp);
	// free_matrix(tokens);
	free(concat);
	// free_matrix(final_tokens);
}
int	main(int ac, char **av, char **envp)
{
	char	*str;

	(void)ac;
	(void)av;
	signal(3, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		str = readline("minishell>>> ");
		if (!str)
		{
			free(str);
			exit(0);
		}
		faz_tudo(str, envp);
		free(str);
	}
	return (0);
}
