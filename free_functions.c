/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:26:17 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/04 22:06:53 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envs(t_env *envs)
{
	t_env	*temp;

	while (envs)
	{
		temp = envs;
		envs = envs->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	free_all(t_shell *shell)
{
	free_envs(shell->envs);
	free_commands(shell->commands);
}

void	free_redirections(t_redirection *redir)
{
	t_redirection	*temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		free(temp->file);
		free(temp);
	}
}

void	free_commands(t_command *cmd)
{
	t_command	*temp;

	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		free_matrix(temp->args);
		free_redirections(temp->redirs);
		free(temp);
	}
}
