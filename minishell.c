/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:00:27 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/27 08:17:31 by pgaspar          ###   ########.fr       */
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
int	main(void)
{
	char	*str;
	char	*concat;
	char	**str3;
	char	**str2;

	str2 = ft_parse("ls|cat -e<<her_doc>file1>>file2");
	concat = mat_concat(str2);
	str3 = ft_parse2(concat);
	for (int i = 0; str3[i]; i++)
		printf("str3: %s\n", str3[i]);
	printf("string concat: %s\n", concat);
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
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
