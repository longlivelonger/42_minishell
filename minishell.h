/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:54:44 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/14 15:40:15 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>

# include "libft/libft.h"
# include "syntax_tree.h"
# include "tokens.h"

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

typedef struct s_global
{
	t_list	*env;
}	t_global;

t_global	g_global;

void	set_readline_signals(void);

int		is_builtin(char **args);
void	run_builtin(char **args);
void	builtin_echo(char **args);
void	builtin_cd(char **args);
void	builtin_pwd(char **args);

void	builtin_exit(char **args);
void	builtin_export(char **args);
void	builtin_unset(char **args);
void	builtin_env(char **args);

void	delete_env_content(void *content);

#endif