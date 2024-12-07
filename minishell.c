/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:00:27 by pgaspar           #+#    #+#             */
/*   Updated: 2024/12/07 14:12:37 by pgaspar          ###   ########.fr       */
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
	int		i;
	int		original_fd[2];
	char	**command;

	i = 0;
	original_fd[0] = dup(0);
	original_fd[1] = dup(1);
	while (tokens[i])
	{
		// printf("Token: %s\n", tokens[i]);
		command = ft_split(tokens[i], ' ');
		/* for (int j = 0; command[j]; j++)
			printf("Command: %s\n", command[j]); */
		if (tokens[i + 1] && !ft_strcmp(tokens[i + 1], "|"))
		{
			i++;
			// printf("pipe\n");
			pipe_it(command, envp);
		}
		else if (tokens[i + 1] && !ft_strcmp(tokens[i + 1], ">"))
		{
			i += 2;
			// printf("redir\n");
			right_redir(command, envp, tokens[i]);
		}
		else
		{
			dup2(original_fd[1], 1);
			close(original_fd[1]);
			just_execute(command, envp);
		}
		free_matrix(command);
		i++;
	}
	dup2(original_fd[0], 0);
	close(original_fd[0]);
}

void	faz_tudo(char *str, char **envp)
{
	char	**tokens;
	char	**final_tokens;
	char	*concat;

	tokens = ft_parse(str);
	concat = mat_concat(tokens);
	final_tokens = ft_parse2(concat);
	/* printf("Concat: %s\n", concat);
	for (int i = 0; tokens[i]; i++)
		printf("Token: %s\n", tokens[i]);
	for (int i = 0; final_tokens[i]; i++)
		printf("Final token: %s\n", final_tokens[i]); */
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
