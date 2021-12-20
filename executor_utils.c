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

int	dup_redirected_io(int (*fd_pipe)[2], int mode)
{
	int	fd_pipe_1;

	if (mode)
	{
		fd_pipe_1 = pipe(*fd_pipe);
		fd_pipe_1 = *fd_pipe[1];
		dup2(fd_pipe_1, 1);
		return (fd_pipe_1);
	}
	fd_pipe_1 = *fd_pipe[0];
	dup2(fd_pipe_1, 0);
	return (fd_pipe_1);
}

char	*find_env_value(char *key, int key_len, char **env, int *env_value_len)
{
	int	env_key_len;

	while (env)
	{
		env_key_len = 0;
		while (*(*env + env_key_len) && *(*env + env_key_len) != '=')
			env_key_len++;
		if (env_key_len == key_len)
		{
			if (!ft_strncmp(key, *env, key_len))
			{
				*env_value_len = 0;
				while (*(*env + env_key_len + *env_value_len + 1))
					(*env_value_len)++;
				return (*env);
			}
		}
		env++;
	}
	return (NULL);
}

int	ext_close(int	fd)
{
	if (fd != -1)
		return (close(fd));
	else
		return (fd);
}

int	ext_pipe_close(int pipe[2], int	end_to_close)
{
	if (pipe[0] != -1)
		return (close(pipe[end_to_close]));
	else
		return (pipe[0]);
}

int	ext_open(char *file, int fd, int end_to_open, int in_flag, int out_flag)
{
	int	temp_fd;

	if (file)
	{
		temp_fd = fd;
		if (end_to_open == 0)
		{	
			(void) in_flag;
			fd = open(file, O_RDONLY);
			dup2(fd, 0);
			if (temp_fd != -1)
				close(temp_fd);
		}
		else
		{
			fd = open(file, O_WRONLY | O_CREAT | out_flag, S_IRUSR | S_IWUSR);
			dup2(fd, 1);
			if (temp_fd != -1)
				close(temp_fd);
		}
	}
	return (fd);
}
