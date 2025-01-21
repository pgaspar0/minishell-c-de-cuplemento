/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_funcional.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 07:35:19 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/21 07:35:21 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_unset(t_env **env, char *var)
{
	t_env *current;
	t_env *prev;

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