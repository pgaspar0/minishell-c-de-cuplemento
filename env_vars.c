/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:23:10 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/16 11:44:13 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	t_env	*current;
	char	*equal;
	int		i;

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

static int	env_to_matrix_loop(t_env *current, char **env_matrix)
{
	int		i;
	char	*temp;

	i = 0;
	while (current)
	{
		if (current->value)
		{
			temp = ft_strjoin(current->key, "=");
			env_matrix[i] = ft_strjoin(temp, current->value);
			free(temp);
			if (!env_matrix[i])
			{
				while (i-- > 0)
					free(env_matrix[i]);
				free(env_matrix);
				return (-1);
			}
			i++;
		}
		current = current->next;
	}
	env_matrix[i] = NULL;
	return (0);
}

char	**env_to_matrix(t_env *env_list)
{
	t_env	*current;
	char	**env_matrix;
	int		count;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	env_matrix = malloc((count + 1) * sizeof(char *));
	if (!env_matrix)
		return (NULL);
	current = env_list;
	if (env_to_matrix_loop(current, env_matrix) == -1)
		return (NULL);
	return (env_matrix);
}
