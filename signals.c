/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:12:27 by gamekiller2       #+#    #+#             */
/*   Updated: 2025/02/08 18:07:09 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit(int sig)
{
	(void)sig;
	g_status_changer(131);
	write(2, "Quit (core dumped)\n", 19);
	rl_on_new_line();
	if (g_int(-1) == 0)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_status_changer(130);
	write(1, "\n", 1);
	rl_on_new_line();
	if (g_int(-1) == 0)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_on_off(int flag)
{
	if (flag == 0)
	{
		g_int(1);
		signal(SIGQUIT, sigquit);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		g_int(0);
	}
}
