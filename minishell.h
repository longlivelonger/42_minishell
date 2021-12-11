/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:54:44 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/11 15:26:17 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>

# include "libft/libft.h"

void	run_command(char *command);

void	set_readline_signals(void);

void	builtin_echo(char **args);

#endif