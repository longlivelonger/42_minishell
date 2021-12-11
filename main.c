/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:17:42 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/11 15:53:12 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	run_command(char *command)
// {
// 	// printf("%s\n", command);
// 	builtin_echo(ft_split(command, ' '));
// }

int	main(int argc, char **argv)
{
	char	*command_line;

	(void) argc;
	(void) argv;
	while (1)
	{
		set_readline_signals();
		command_line = 0;
		command_line = readline("$ ");
		if (command_line == 0)
		{
			rl_clear_history();
			return (0);
		}
		if (command_line != 0 && ft_strlen(command_line) > 0)
		{
			add_history(command_line);
			run_command(command_line);
		}
		if (command_line != 0)
			free(command_line);
	}
	return (0);
}
