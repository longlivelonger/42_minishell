/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:10:22 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/21 13:52:34 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_atoi(const char *str)
{
	long int	num;
	int			i;
	int			minus;

	minus = 0;
	num = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			minus = 1;
	i--;
	while (str[++i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		if (num < 0 && !minus)
			return (-1);
		if (-num > 0 && minus)
			return (-1);
	}
	if (minus && (num % 256) > 0)
		return ((int)(256 - num % 256));
	return ((int)(num % 256));
}

static int	is_numeric(const char *str)
{
	int	i;
	int	minus;

	minus = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			minus = 1;
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	return (0);
}

static int	get_exit_status(const char *str)
{
	if (!is_numeric(str))
		return (-1);
	return (special_atoi(str));
}

void	builtin_exit(char **args)
{
	int	num;

	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "exit", 5) != 0)
		return ;
	ft_putstr_fd("exit\n", 2);
	if (args[1] == 0)
		clear_global_n_exit(0);
	if (args[1] != 0)
	{
		num = get_exit_status(args[1]);
		if (num == -1)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			clear_global_n_exit(255);
		}
	}
	if (args[1] != 0 && args[2] == 0)
		clear_global_n_exit(num);
	else
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_global.exit_status = 1;
	}
}
