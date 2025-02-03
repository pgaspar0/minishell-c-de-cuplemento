/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_builtins2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:53:26 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/03 11:03:09 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_multiple(t_env **env, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_unset(env, args[i]);
		i++;
	}
}

void	ft_export_multiple(t_env **env, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_export(env, args[i]);
		i++;
	}
}

char	*ft_getenv(const char *varname, t_env *env_list)
{
	size_t	var_len;
	t_env	*current;
	char	*var_value;

	if (varname == NULL || env_list == NULL)
		return (NULL);
	var_len = ft_strlen(varname);
	current = env_list;
	while (current)
	{
		if (ft_strncmp(varname, current->key, var_len) == 0
			&& current->key[var_len] == '\0')
		{
			var_value = ft_strdup(current->value);
			return (var_value);
		}
		current = current->next;
	}
	return (NULL);
}
