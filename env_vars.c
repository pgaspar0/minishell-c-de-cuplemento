/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:23:10 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/09 12:25:35 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env *head;
	t_env *new_node;
	t_env *current;
	char *equal;
	int i;

	i = 0;
	head = NULL;
	current = NULL;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		new_node = malloc(sizeof(t_env));
		new_node->key = ft_substr(envp[i], 0, equal - envp[i]);
		new_node->value = ft_strdup(equal + 1);
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
