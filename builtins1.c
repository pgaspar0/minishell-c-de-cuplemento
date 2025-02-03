/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:48:04 by jorcarva          #+#    #+#             */
/*   Updated: 2025/02/03 14:53:24 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_command2(char **args)
{
	if (strcmp(args[0], "export") == 0)
		return (1);
	else if (strcmp(args[0], "unset") == 0)
		return (1);
	else if (strcmp(args[0], "env") == 0)
		return (1);
	else if (strcmp(args[0], "exit") == 0)
		return (1);
	return (0);
}

int	is_builtin_command(char **args)
{
	if (!args || !args[0])
		return (0);
	if (strcmp(args[0], "echo") == 0)
		return (1);
	else if (strcmp(args[0], "cd") == 0)
		return (1);
	else if (strcmp(args[0], "pwd") == 0)
		return (1);
	else
		return (is_builtin_command2(args));
	return (0);
}
