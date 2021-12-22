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

int	dup_redirected_io(int (fd_pipe)[2], int *fd_pipe_out,
		int *fd_pipe_in, t_job *is_next_job)
{
	errno = 0;
	if (*fd_pipe_out != -1)
	{
		*fd_pipe_in = fd_pipe[0];
		dup2(*fd_pipe_in, 0);
	}
	if (is_next_job)
	{
		*fd_pipe_out = pipe(fd_pipe);
		*fd_pipe_out = fd_pipe[1];
		dup2(*fd_pipe_out, 1);
	}
	if (errno)
	{
		write(2, "minishell: ", 11);
		perror("dup2: ");
		ext_close(*fd_pipe_in);
		ext_close(*fd_pipe_out);
		return (1);
	}
	return (0);
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

static void	init_here_doc_vars(int count[2], int *max_count,
	int fd_pipe[2], char *delim)
{
	count[0] = 0;
	count[1] = 0;
	*max_count = ft_strlen(delim);
	pipe(fd_pipe);
}

int	open_here_doc(char *delim)
{
	char	c[256];
	int		count[2];
	int		max_count;
	int		fd_pipe[2];

	init_here_doc_vars(count, &max_count, fd_pipe, delim);
	while (read(0, c + count[0], 1))
	{
		count[0]++;
		if (*(c + count[0] - 1) == '\n')
		{
			if (count[1] == max_count)
				break ;
			write(fd_pipe[1], c, count[0]);
			count[0] = 0;
			count[1] = 0;
		}
		else if (*(c + count[0] - 1) == *(delim + count[1])
			&& count[0] < (max_count + 1))
			count[1]++;
		else
			count[1] = 0;
	}
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}
