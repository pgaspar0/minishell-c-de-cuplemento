/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:00:27 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/27 12:54:47 by pgaspar          ###   ########.fr       */
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

void	pipex(char **tokens)
{
	
}

void	faz_tudo(char *str)
{
	char	**tokens;
	char 	**final_tokens;
	char	*concat;

	tokens = ft_parse(str);
	concat = mat_concat(tokens);
	final_tokens = ft_parse2(concat);
	pipex(final_tokens);
	free(tokens);
	free(concat);
	free(final_tokens);
}
int	main(void)
{
	char	*str;

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
		faz_tudo(str);
		free(str);
	}
	return (0);
}
