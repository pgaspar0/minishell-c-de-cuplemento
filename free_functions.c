/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:26:17 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/31 17:58:33 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function to free everything in shell struct if exists in the end of the program


// function to free the envs list

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
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		free_matrix(shell->tokens);
	if (shell->commands)
		free_commands(shell->commands);
	if (shell->envs)
		free_envs(shell->envs);
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
