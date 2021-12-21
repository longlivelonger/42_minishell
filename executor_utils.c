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

int	ext_close(int fd)
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

int	open_here_doc(char *delim)
{
	char	c[256];
	int		count;
	int		delim_count;
	int		max_count;
	int		fd_pipe[2];

	count = 0;
	delim_count = 0;
	max_count = ft_strlen(delim);
	pipe(fd_pipe);
	while (read(0, c + count, 1))
	{
		count++;
		if (*(c + count - 1) == '\n')
		{
			if (delim_count == max_count)
				break;
			write(fd_pipe[1], c, count);
			count = 0;
			delim_count = 0;
		}
		else if (*(c + count - 1) == *(delim + delim_count) && count < (max_count + 1))
			delim_count++;
		else
			delim_count = 0;
	}
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}
