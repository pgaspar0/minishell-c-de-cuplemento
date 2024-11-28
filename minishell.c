/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:00:27 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/28 17:43:51 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void debug_tokens(char **tokens, const char *label)
{
    printf("Debugging tokens: %s\n", label);
    if (!tokens)
    {
        printf("Tokens array is NULL.\n");
        return;
    }
    for (int i = 0; tokens[i]; i++)
        printf("Token[%d]: '%s'\n", i, tokens[i]);
}

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
	for (int i = 0; tokens[i]; i++)
		printf("%s\n", tokens[i]);
}

void	faz_tudo(char *str)
{
	char	**tokens;
	char 	**final_tokens;
	char	*concat;

	tokens = ft_parse(str);
	debug_tokens(tokens, "ft_parse");
	concat = mat_concat(tokens);
	printf("Concat: %s\n", concat);
	final_tokens = ft_parse2(concat);
	debug_tokens(final_tokens, "ft_parse2");
	pipex(final_tokens);
	free_matrix(tokens);
	free(concat);
	free_matrix(final_tokens);
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
