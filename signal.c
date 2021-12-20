/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:32:47 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/20 15:48:41 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_readline_handler(int sig)
{
	(void) sig;
	g_global.exit_status = 1;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_exec_handler(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 1);
	g_global.exit_status = 130;
}

static void	sigquit_exec_handler(int sig)
{
	(void) sig;
	g_global.exit_status = 131;
}

void	set_readline_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &sigint_readline_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_exec_signals(void)
{
	signal(SIGINT, &sigint_exec_handler);
	signal(SIGQUIT, &sigquit_exec_handler);
}
