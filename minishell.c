/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:00:27 by pgaspar           #+#    #+#             */
/*   Updated: 2024/11/04 18:50:23 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	signal(3, SIG_IGN);
	while (1)
	{
		str = readline("minihell>>> ");
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
