/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:00:27 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/01 17:41:26 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[])
{
	int	i;
	char	*path;
	char	**paths;
	char	*str;
	char	**entry;

	(void)ac;
	(void)av;
	path = getenv("PATH");
	paths = ft_split(path, ':');
	signal(3, SIG_IGN);
	while (1)
	{
		str = readline("minihell>>> ");
		entry = ft_split(str, 32);
		i = 0;
		if (!str)
		{
			free(str);
			free(path);
			free_matrix(entry);
			free_matrix(paths);
			exit(0);
		}
		printf("%s\n", str);
		free_matrix(entry);
		free(str);
	}
	free(path);
	free_matrix(paths);
	return (0);
}
