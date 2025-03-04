/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:50:46 by jorcarva          #+#    #+#             */
/*   Updated: 2025/02/08 17:40:50 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_only_n(char *word)
{
	int	i;

	i = 0;
	if (!word || *word == '\0')
		return (0);
	if (word[i++] != '-')
		return (0);
	while (word[i])
	{
		if (word[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

bool	identify_n(char **args, int *start_index)
{
	bool	suppress_newline;

	suppress_newline = false;
	while (args[*start_index] && (strcmp(args[*start_index], "-n") == 0
			|| is_only_n(args[*start_index]) == 1))
	{
		suppress_newline = true;
		(*start_index)++;
	}
	return (suppress_newline);
}

void	ft_echo(char **args)
{
	bool	suppress_newline;
	int		start_index;
	int		i;

	suppress_newline = false;
	start_index = 1;
	suppress_newline = identify_n(args, &start_index);
	i = start_index;
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!suppress_newline)
		printf("\n");
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	ft_cd(char **input_path)
{
	char	*current_dir;
	char	*path;

	path = NULL;
	path = input_path[1];
	if (!path)
	{
		ft_putstr_fd("cd : too few arguments\n", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	current_dir = getcwd(NULL, 0);
	if (current_dir)
		free(current_dir);
	else
		perror("getcwd");
	return (0);
}
