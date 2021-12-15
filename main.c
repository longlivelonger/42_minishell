/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:17:42 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/15 17:26:35 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global(void)
{
	t_kv	*kv;

	kv = malloc(sizeof(*kv));
	if (kv == 0)
		return ;
	kv->name = ft_strdup("PATH");
	kv->value = ft_strdup(getenv(kv->name));
	g_global.env = ft_lstnew(kv);
}

int	main(int argc, char **argv)
{
	char	*command_line;

	(void) argc;
	(void) argv;
	init_global();
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
			parse_n_execute(command_line);
		}
		if (command_line != 0)
			free(command_line);
	}
	return (0);
}
