/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:07:39 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/21 14:59:00 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_path(char **path)
{
	char	*temp;
	char	*temp2;

	if ((*path)[0] != '~')
		return (*path);
	temp = ft_strjoin(get_env("HOME"), (*path) + 1);
	free(*path);
	*path = temp;
	while (ft_strchr(*path, '~'))
	{
		temp2 = ft_strchr(*path, '~') + 1;
		ft_strchr(*path, '~')[0] = '\0';
		temp = ft_strjoin(*path, get_env("HOME"));
		temp2 = ft_strjoin(temp, temp2);
		free(*path);
		*path = temp2;
		free(temp);
	}
	return (*path);
}

static void	cd_to_home(void)
{
	char	*oldpwd;

	oldpwd = getcwd(0, 0);
	if (get_env("HOME") == 0)
	{
		write(2, "cd: HOME not set\n", 17);
		g_global.exit_status = 1;
		return ;
	}
	else if (chdir(get_env("HOME")) == -1)
	{
		perror("cd");
		g_global.exit_status = 1;
		return ;
	}
	set_env("OLDPWD", oldpwd);
	set_env("PWD", getcwd(0, 0));
}

void	builtin_cd(char **args)
{
	char	*path;
	char	*oldpwd;

	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "cd", 3) != 0)
		return ;
	if (args[1] == 0)
	{
		cd_to_home();
		return ;
	}
	oldpwd = getcwd(0, 0);
	path = ft_strdup(args[1]);
	if (chdir(process_path(&path)) == -1)
	{
		perror("cd");
		g_global.exit_status = 1;
		free(path);
		return ;
	}
	set_env(ft_strdup("OLDPWD"), oldpwd);
	set_env(ft_strdup("PWD"), getcwd(0, 0));
	free(path);
}
