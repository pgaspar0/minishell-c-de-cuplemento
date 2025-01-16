/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:32:27 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/16 12:31:37 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_commands(char **tokens)
{
	t_command		*head;
	t_command		*current;
	t_redirection	*last_redir;
	t_redirection	*redir;
	size_t			arg_count;

	head = NULL;
	current = NULL;
	for (int i = 0; tokens[i];)
	{
		if (!current)
		{
			current = malloc(sizeof(t_command));
			current->args = malloc(sizeof(char *) * 1024);
			current->redirs = NULL;
			last_redir = NULL;
			current->next = NULL;
			if (!head)
				head = current;
		}
		arg_count = 0;
		while (tokens[i] && tokens[i][0] != '|')
		{
			if (tokens[i][0] == '<' || tokens[i][0] == '>')
			{
				redir = malloc(sizeof(t_redirection));
				redir->type = (tokens[i][0] == '>') + (tokens[i][1] == '>');
				if (tokens[i][0] == '<' && tokens[i][1] == '<')
					redir->type = 3;
				redir->file = ft_strdup(tokens[++i]);
				redir->next = NULL;
				if (!last_redir)
					current->redirs = redir;
				else
					last_redir->next = redir;
				last_redir = redir;
			}
			else
			{
				current->args[arg_count++] = ft_strdup(tokens[i]);
			}
			i++;
		}
		current->args[arg_count] = NULL;
		if (tokens[i] && tokens[i][0] == '|')
		{
			current->next = malloc(sizeof(t_command));
			if (!current->next)
				return (NULL);
			current = current->next;
			current->args = malloc(sizeof(char *) * 1024);
			if (!current->args)
				return (NULL);
			current->redirs = NULL;
			last_redir = NULL;
			current->next = NULL;
			i++;
		}
	}
	return (head);
}
