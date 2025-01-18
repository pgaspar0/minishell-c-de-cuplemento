/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:41:54 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/18 14:27:32 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	try_exit(t_shell *shell, t_env *env)
{
	char	**cmds;

	cmds = ft_split_masgo(shell->input, ' ');
	if (ft_strcmp("exit", cmds[0]) == 0)
	{
		if (ft_exit(cmds, NULL, shell, env))
		{
			free_all_s(cmds);
			handle_exit(shell, env);
			return (1);
		}
		free_all_s(cmds);
		return (-1);
	}
	free_all_s(cmds);
	return (0);
} */

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

int	ft_exit(t_env **env, char **args, char *exit_code)
{
	ft_putstr_fd("exit\n", 2);
	if (!args[1])
	{
		update_env(env, "?", "0");
        exit(0);	
	}
	if (!is_nbr(args[1]) || (ft_atol(args[1]) < INT_MIN
			|| ft_atol(args[1]) > INT_MAX))
	{
		print_error(args[1]);
		update_env(env, "?", "2");
		return (1);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		update_env(env, "?", "1");
		return (0);
	}
	exit_code = ft_itoa(exit_func(args[1]));
	g_exit_status = ft_atoi(exit_code);
	update_env(env, "?", exit_code);
	free(exit_code);
	// return (1);
    exit(g_exit_status);
}