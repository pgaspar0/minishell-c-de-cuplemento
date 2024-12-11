/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:01:11 by pgaspar           #+#    #+#             */
/*   Updated: 2024/12/11 18:25:56 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "pipex.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_redirection
{
	char					*file;
	int						type;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command
{
	char					**args;
	t_redirection			*redirs;
	struct s_command		*next;
}							t_command;

char	**ft_parse(const char *s);
char	**ft_parse2(const char *s);
char	*mat_concat(char **mat);

#endif
