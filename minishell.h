/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:01:11 by pgaspar           #+#    #+#             */
/*   Updated: 2025/01/07 11:50:37 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "pipex.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

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

char						**ft_parse(const char *s);
char						**ft_parse2(const char *s);
char						*mat_concat(char **mat);

#endif
