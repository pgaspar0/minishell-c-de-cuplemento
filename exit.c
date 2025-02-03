/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:41:54 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/03 13:56:29 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_nbr(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	exit_func(char *exit_code)
{
	int	code;

	code = ft_atoi(exit_code);
	if (code < 0)
		code = 256 + (code % 256);
	if (code > 255)
		return (code % 256);
	return (code);
}

void	print_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

//int	ft_exit(t_shell *shell)
int	ft_exit(t_env **env, char **args, char *exit_code, t_shell *shell)
{
	ft_putstr_fd("exit\n", 2);
	if (!args[1])
	{
		update_env(env, "?", "0", 2);
		free_commands(shell->commands);
		free_envs(shell->envs);
		free(shell->input);
		free_matrix(shell->tokens);
		exit(0);
	}
	if (!is_nbr(args[1]) || (ft_atol(args[1]) < INT_MIN
			|| ft_atol(args[1]) > INT_MAX))
	{
		print_error(args[1]);
		update_env(env, "?", "2", 2);
		free_commands(shell->commands);
		free_envs(shell->envs);
		free(shell->input);
		free_matrix(shell->tokens);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		update_env(env, "?", "1", 2);
		return (1);
	}
	exit_code = ft_itoa(exit_func(args[1]));
	g_status_changer(ft_atoi(exit_code));
	update_env(env, "?", exit_code, 2);
	free(exit_code);
		free_commands(shell->commands);
		free_envs(shell->envs);
		free(shell->input);
		free_matrix(shell->tokens);
	exit(g_status_changer(-1));
}
