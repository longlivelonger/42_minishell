/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:54:29 by dweeper           #+#    #+#             */
/*   Updated: 2021/12/09 17:17:26 by dweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	command_nfound_err(char *name)
{
	write(2, name, ft_strlen(name));
	write(2, ": command not found\n", 20);
	return (-2);
}

int	launch_buildin(char **args)
{
	int	status;

	status = 0;
	errno = 0;
	g_global.exit_status = 0;
	run_builtin(args);
	if (errno)
	{
		write(2, "-minishell: ", 12);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": ", 2);
		perror(args[1]);
		status = -1;
	}
	return (status);
}

int	check_exit_status(int exit_status, int launch_return)
{
	if (launch_return == -2)
	{
		g_global.exit_status = 127;
		return (0);
	}
	else if (launch_return < 1)
	{
		if (launch_return == -1)
			g_global.exit_status = 1;
		else
			g_global.exit_status = 0;
		return (0);
	}
	if (WIFEXITED(exit_status))
		g_global.exit_status = WEXITSTATUS(exit_status);
	else
		g_global.exit_status = 0;
	return (0);
}
