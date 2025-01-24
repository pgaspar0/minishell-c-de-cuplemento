/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:36:36 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/23 16:50:09 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_env **env, char *var)
{
	t_env	*current;
	t_env	*prev;

	while (*env && ft_strcmp((*env)->key, var) == 0)
	{
		current = *env;
		*env = (*env)->next;
		free(current->key);
		free(current->value);
		free(current);
	}
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->key)
		{
			if (env->flag == 0)
			{
				printf("%s=", env->key);
				if (env->value)
					printf("%s\n", env->value);
				else
					printf("\n");
			}
		}
		env = env->next;
	}
}

int	is_valid_identifier(char *key)
{
	int	i;

	if (!key || !ft_isalpha(key[0]) || key[0] == '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	update_env(t_env **env, char *key, char *value, int flag)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (value)
			{
				free(current->value);
				if (current->flag != flag)
					current->flag = flag;
				current->value = ft_strdup(value);
			}
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
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

void	ft_export(t_env **env, char *var)
{
	int		flag;
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(var, '=');
	if (!equal)
	{
		key = ft_strdup(var);
		value = NULL;
		flag = 1;
	}
	else
	{
		key = ft_substr(var, 0, equal - var);
		value = ft_strdup(equal + 1);
		flag = 0;
	}
	if (!is_valid_identifier(key))
	{
		printf("export: `%s': not a valid identifier\n", key);
		free(key);
		free(value);
		return ;
	}
	update_env(env, key, value, flag);
	free(key);
	free(value);
}
