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
	write(2, "minishell: ", 11);
	write(2, name, ft_strlen(name));
	write(2, ": command not found\n", 20);
	return (-2);
}

int	launch_buildin(char **args)
{
	run_builtin(args);
	return (-3);
}

int	check_exit_status(int exit_status, int launch_return)
{
	if (launch_return == -3)
		return (0);
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
	return (0);
}

int	open_input_stream(char *file, int fd, int in_flag)
{
	int	temp_fd;

	if (file)
	{
		temp_fd = fd;
		if (in_flag)
			fd = open_here_doc(file);
		else
			fd = open(file, O_RDONLY);
		dup2(fd, 0);
		if (temp_fd != -1)
			close(temp_fd);
	}
	return (fd);
}

int	open_output_stream(char *file, int fd, int out_flag)
{
	int	temp_fd;

	if (file)
	{
		temp_fd = fd;
		fd = open(file, O_WRONLY | O_CREAT | out_flag, S_IRUSR | S_IWUSR);
		dup2(fd, 1);
		if (temp_fd != -1)
			close(temp_fd);
	}
	return (fd);
}
