/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:18 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/12 12:23:55 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **args)
{
	if (args == 0 || args[0] == 0)
		return (0);
	if (ft_strncmp(args[0], "echo", 5))
		return (1);
	if (ft_strncmp(args[0], "cd", 3))
		return (1);
	if (ft_strncmp(args[0], "pwd", 4))
		return (1);
	if (ft_strncmp(args[0], "export", 7))
		return (1);
	if (ft_strncmp(args[0], "unset", 6))
		return (1);
	if (ft_strncmp(args[0], "env", 4))
		return (1);
	if (ft_strncmp(args[0], "exit", 5))
		return (1);
	return (0);
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
		write(1, args[0], ft_strlen(args[0]));
		print_space = 1;
	}
	if (print_nl)
		write(1, "\n", 1);
}

void	builtin_cd(char **args)
{
	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "cd", 3) != 0)
		return ;
	if (args[1] == 0 || chdir(args[1]) == -1)
		return ;
}
