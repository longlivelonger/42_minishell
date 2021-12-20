/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:17:42 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/20 12:03:22 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*command_line;

	(void) argc;
	(void) argv;
	init_global(envp);
	while (1)
	{
		set_readline_signals();
		command_line = 0;
		command_line = readline(MINISHELL_PROMPT);
		if (command_line == 0)
		{
			rl_clear_history();
			clear_global_n_exit(0);
		}
		if (command_line != 0 && ft_strlen(command_line) > 0)
		{
			add_history(command_line);
			set_exec_signals();
			parse_n_execute(command_line);
		}
		if (command_line != 0)
			free(command_line);
	}
	return (0);
}
