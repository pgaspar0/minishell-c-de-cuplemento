/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:36:36 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/05 15:03:13 by jorcarva         ###   ########.fr       */
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
		unset_free(current);
	}
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			prev->next = current->next;
			unset_free(current);
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
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != ' ' && key[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	update_env(t_env **env, char *key, char *value, int flag)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			update_existing_env(current, value, flag);
			return ;
		}
		current = current->next;
	}
	add_new_env(env, key, value, flag);
}

void	ft_export(t_env **env, char *var)
{
	char	*key;
	char	*value;
	int		flag;

	parse_var(var, &key, &value, &flag);
	printf("key value: %s\n",key);
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
