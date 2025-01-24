/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_builtins3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:49:15 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/23 16:45:05 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;
	int		temp_flag;

	temp_key = a->key;
	temp_value = a->value;
	temp_flag = a->flag;
	a->key = b->key;
	a->value = b->value;
	a->flag = b->flag;
	b->key = temp_key;
	b->value = temp_value;
	b->flag = temp_flag;
}

static void	sort_list_env(t_env **env)
{
	t_env	*ptr1;
	t_env	*lptr;
	int		swapped;

	lptr = NULL;
	swapped = 1;
	if (*env == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *env;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) < 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

t_env	*copy_env(t_env **env)
{
	t_env	*tmp;
	t_env	*new;

	new = NULL;
	tmp = *env;
	while (tmp != NULL)
	{
		if (tmp->flag != 2 && ft_strcmp(tmp->key, "_") != 0)
			update_env(&new, tmp->key, tmp->value, tmp->flag);
		tmp = tmp->next;
	}
	return (new);
}

void	ft_export_no(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = copy_env(env);
	sort_list_env(&tmp);
	while (tmp)
	{
		write(1, "declare -x ", 12);
		write(1, tmp->key, ft_strlen(tmp->key));
		if (tmp->flag == 0)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	update_env(env, "?", "0", 2);
}
