/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:03:05 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/22 16:12:10 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_global_n_exit(int exit_status)
{
	ft_lstclear(&g_global.env, &delete_env_content);
	rl_clear_history();
	exit(exit_status);
}

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
			clear_global_n_exit(1);
		}
		if (g_global.env == 0)
			g_global.env = ft_lstnew(kv);
		else
			ft_lstadd_back(&g_global.env, ft_lstnew(kv));
		envp++;
	}
	delete_env_variable("OLDPWD");
}
