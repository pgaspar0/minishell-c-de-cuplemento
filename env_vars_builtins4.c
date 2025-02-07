/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_builtins4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:23:15 by gamekiller2       #+#    #+#             */
/*   Updated: 2025/02/07 12:45:19 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_existing_env(t_env *current, char *value, int flag)
{
	if (value)
	{
		free(current->value);
		if (current->flag != flag)
			current->flag = flag;
		current->value = ft_strdup(value);
	}
}

void	add_new_env(t_env **env, char *key, char *value, int flag)
{
	t_env	*new_node;

	new_node = ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->flag = flag;
	new_node->next = *env;
	*env = new_node;
}

void	unset_free(t_env *current)
{
	free(current->key);
	free(current->value);
	free(current);
}

void	parse_var(char *var, char **key, char **value, int *flag)
{
	char	*equal;

	equal = ft_strchr(var, '=');
	if (!equal)
	{
		*key = ft_strdup(var);
		*value = NULL;
		*flag = 1;
	}
	else
	{
		*key = ft_substr(var, 0, equal - var);
		*value = ft_strdup(equal + 1);
		*flag = 0;
	}
}
