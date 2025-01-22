/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:32:27 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/22 07:50:42 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parser(t_parser *parser)
{
	parser->current = malloc(sizeof(t_command));
	parser->current->args = malloc(sizeof(char *) * 1024);
	parser->current->redirs = NULL;
	parser->last_redir = NULL;
	parser->current->next = NULL;
	if (!parser->head)
		parser->head = parser->current;
}

void	proccess_tokens_loop(t_parser *parser, char **tokens, int *i)
{
	while (tokens[*i] && tokens[*i][0] != '|')
	{
		if (tokens[*i][0] == '<' || tokens[*i][0] == '>')
		{
			parser->redir = malloc(sizeof(t_redirection));
			parser->redir->type = (tokens[*i][0] == '>')
				+ (tokens[*i][1] == '>');
			if (tokens[*i][0] == '<' && tokens[*i][1] == '<')
				parser->redir->type = 3;
			parser->redir->file = ft_strdup(tokens[++(*i)]);
			parser->redir->next = NULL;
			if (!parser->last_redir)
				parser->current->redirs = parser->redir;
			else
				parser->last_redir->next = parser->redir;
			parser->last_redir = parser->redir;
		}
		else
			parser->current->args[parser->arg_count++] = ft_strdup(tokens[*i]);
		(*i)++;
	}
}

int	handle_pipes(t_parser *parser, int *i)
{
	parser->current->next = malloc(sizeof(t_command));
	if (!parser->current->next)
		return (0);
	parser->current = parser->current->next;
	parser->current->args = malloc(sizeof(char *) * 1024);
	if (!parser->current->args)
		return (0);
	parser->current->redirs = NULL;
	parser->last_redir = NULL;
	parser->current->next = NULL;
	(*i)++;
	return (1);
}

t_command	*parse_commands(char **tokens)
{
	int			i;
	t_parser	parser;

	i = 0;
	parser.head = NULL;
	parser.current = NULL;
	while (tokens[i])
	{
		if (!parser.current)
			init_parser(&parser);
		parser.arg_count = 0;
		proccess_tokens_loop(&parser, tokens, &i);
		parser.current->args[parser.arg_count] = NULL;
		if (tokens[i] && tokens[i][0] == '|')
			if (!handle_pipes(&parser, &i))
				return (NULL);
	}
	return (parser.head);
}
