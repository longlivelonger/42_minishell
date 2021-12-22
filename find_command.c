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

#include "minishell.h"

static char	*get_dir_name(char *path, int *count)
{
	char	*dir_name;
	int		start_count;

	start_count = *count;
	if (!(*(path + *count)))
		return (NULL);
	while (*(path + *count) && *(path + *count) != ':')
	{
		(*count)++;
	}
	dir_name = malloc(sizeof(char) * (*count - start_count + 1));
	if (!dir_name)
		return (NULL);
	ft_strlcpy(dir_name, path + start_count, *count - start_count + 1);
	if (*(path + *count))
		(*count)++;
	return (dir_name);
}

static int	build_command_name(char *dir_name, char **com_name,
	char *is_path_alloc)
{
	char	*full_path;
	int		dir_name_l;
	int		com_name_l;

	dir_name_l = ft_strlen(dir_name);
	com_name_l = ft_strlen(*com_name);
	full_path = malloc(sizeof(char) * (dir_name_l + com_name_l + 2));
	*is_path_alloc = 1;
	ft_strlcpy(full_path, dir_name, dir_name_l + 1);
	full_path[dir_name_l] = '/';
	ft_strlcpy(full_path + dir_name_l + 1, *com_name, com_name_l + 1);
	*com_name = full_path;
	return (1);
}

static int	search_directory(char *next_dir, char **path_name,
	char *is_path_alloc)
{
	int				result;
	DIR				*dir;
	struct dirent	*dir_info;

	errno = 0;
	dir = opendir(next_dir);
	dir_info = readdir(dir);
	while (dir && (dir_info))
	{
		if (ft_strcmp_u(*path_name, dir_info->d_name))
			result = build_command_name(next_dir, path_name, is_path_alloc);
		dir_info = readdir(dir);
	}
	closedir(dir);
	free(next_dir);
	if (errno)
	{
		write(2, "-minishell: ", 12);
		write(2, next_dir, ft_strlen(next_dir));
		perror(NULL);
		return (-1);
	}
	return (result);
}

static int	search_in_path(char **path_name, char *path, char *is_path_alloc)
{
	int				dir_count;
	int				result;
	char			*next_dir;

	dir_count = 0;
	result = -1;
	if (!path)
		return (result);
	next_dir = get_dir_name(path, &dir_count);
	while (result != 1 && next_dir)
	{
		result = search_directory(next_dir, path_name, is_path_alloc);
		if (result == -1)
			return (-1);
		if (result != 1)
			next_dir = get_dir_name(path, &dir_count);
	}
	return (result);
}

int	find_command(char **path_name, char **com_name, char *is_path_alloc)
{
	int	count;
	int	last_slash;

	count = 0;
	last_slash = 0;
	while (*(*path_name + count))
	{
		if (*(*path_name + count) == '/')
			last_slash = count;
		count++;
	}
	if (last_slash)
	{
		*com_name = (*path_name + last_slash + 1);
		return (1);
	}
	else
	{
		if (is_builtin(com_name))
			return (0);
		return (search_in_path(path_name, get_env("PATH"), is_path_alloc));
	}
}
