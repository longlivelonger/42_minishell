/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:17:42 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/20 11:53:30 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global(char **envp)
{
	t_kv	*kv;

	g_global.env = 0;
	g_global.exit_status = 0;
	while (envp != 0 && envp[0] != 0)
	{
		kv = create_env_variable(envp[0]);
		if (kv == 0)
		{
			perror("minishell");
			ft_lstclear(&g_global.env, &delete_env_content);
			exit(1);
		}
		if (g_global.env == 0)
			g_global.env = ft_lstnew(kv);
		else
			ft_lstadd_back(&g_global.env, ft_lstnew(kv));
		envp++;
	}
}

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
			return (0);
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
