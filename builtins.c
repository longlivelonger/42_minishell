/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:18 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/22 14:16:31 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **args)
{
	if (args == 0 || args[0] == 0)
		return (0);
	if (ft_strncmp(args[0], "echo", 5) == 0
		|| ft_strncmp(args[0], "cd", 3) == 0
		|| ft_strncmp(args[0], "pwd", 4) == 0
		|| ft_strncmp(args[0], "export", 7) == 0
		|| ft_strncmp(args[0], "unset", 6) == 0
		|| ft_strncmp(args[0], "env", 4) == 0
		|| ft_strncmp(args[0], "exit", 5) == 0)
		return (1);
	return (0);
}

void	run_builtin(char **args)
{
	if (args == 0 || args[0] == 0)
		return ;
	g_global.exit_status = 0;
	if (ft_strncmp(args[0], "echo", 5) == 0)
		builtin_echo(args);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		builtin_cd(args);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		builtin_pwd(args);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		builtin_export(args);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		builtin_unset(args);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		builtin_env(args);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		builtin_exit(args);
}

void	builtin_echo(char **args)
{
	int	print_space;
	int	print_nl;

	print_space = 0;
	print_nl = 1;
	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "echo", 5) != 0)
		return ;
	while ((++args)[0] != 0)
	{
		if (!print_space && ft_strncmp(args[0], "-n", 3) == 0)
		{
			print_nl = 0;
			continue ;
		}
		if (print_space)
			write(1, " ", 1);
		ft_putstr_fd(args[0], 1);
		print_space = 1;
	}
	if (print_nl)
		write(1, "\n", 1);
}

void	builtin_pwd(char **args)
{
	char	*pwd;

	if (args == 0 || args[0] == 0
		|| ft_strncmp(args[0], "pwd", 4) != 0)
	{
		g_global.exit_status = 1;
		return ;
	}
	pwd = getcwd(0, 0);
	if (pwd == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("pwd");
		g_global.exit_status = 1;
		return ;
	}
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
}
