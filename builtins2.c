/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:56:58 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/14 15:44:29 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(char **args)
{
	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "exit", 5) != 0)
		return ;
	exit(0);
}

void	builtin_export(char **args)
{
	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "export", 7) != 0)
		return ;
	exit(0);
}

void	builtin_unset(char **args)
{
	t_list	*prev;
	t_list	*current;

	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "unset", 6) != 0)
		return ;
	if (args[1] == 0)
		return ;
	prev = 0;
	current = g_global.env;
	while (current != 0)
	{
		if (ft_strcmp(((t_env *)(current->content))->name, args[1]) == 0)
		{
			if (prev != 0)
				prev->next = current->next;
			else
				g_global.env = current->next;
			ft_lstdelone(current, &delete_env_content);
		}
		prev = current;
		current = current->next;
	}
}

void	builtin_env(char **args)
{
	t_list	*temp;
	t_env	*variable;

	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "env", 4) != 0)
		return ;
	temp = g_global.env;
	while (temp != 0)
	{
		variable = (t_env *)temp->content;
		if (variable->value)
			printf("%s=%s\n", variable->name, variable->value);
		else
			printf("%s=\n", variable->name);
		temp = temp->next;
	}
}
