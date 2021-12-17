/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:54:44 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/17 13:16:31 by sbronwyn         ###   ########.fr       */
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
# include <sys/param.h>
# include <dirent.h>

# include "libft/libft.h"
# include "syntax_tree.h"
# include "tokens.h"

typedef struct s_kv
{
	char	*name;
	char	*value;
}	t_kv;

typedef struct s_global
{
	t_list	*env;
	int		exit_status;
}	t_global;

t_global	g_global;

void	set_readline_signals(void);
void	set_exec_signals(void);

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
void	print_sorted_env(void);
t_kv	*create_env_variable(char *str);

char	*get_env(char *name);
int		is_valid_env_key(char *name);
void	delete_env_variable(char *name);

#endif