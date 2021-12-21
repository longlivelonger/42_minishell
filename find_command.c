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

static int	ft_strcmp_u(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	if (*str1 != *str2)
		return (0);
	return (1);
}

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

static int	build_command_name(char *dir_name, char **com_name, char *is_path_alloc)
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

static int	search_in_path(char **path_name, char *path, char *is_path_alloc)
{
	int				dir_count;
	int				result;
	DIR				*dir;
	struct dirent	*dir_info;
	char			*next_dir;

	dir_count = 0;
	result = -1;
	if (!path)
		return (result);
	while (result != 1 && (next_dir = get_dir_name(path, &dir_count)))
	{
		dir = opendir(next_dir);
		while (dir && (dir_info = readdir(dir)))
		{
			if(ft_strcmp_u(*path_name, dir_info->d_name))
				result = build_command_name(next_dir, path_name, is_path_alloc);
		}
		closedir(dir);
		free(next_dir);
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
