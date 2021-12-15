/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:56:58 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/15 17:26:21 by sbronwyn         ###   ########.fr       */
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
	char	**arr;

	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "export", 7) != 0)
		return ;
	if (args[1] == 0)
		print_sorted_env();
	if (args[1] != 0)
	{
		arr = ft_split(args[1], '=');
		ft_lstadd_back(&g_global.env,
			ft_lstnew(create_env_variable(arr[0], arr[1])));
		free(arr);
	}
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
		if (ft_strcmp(((t_kv *)(current->content))->name, args[1]) == 0)
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
	t_kv	*kv;

	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "env", 4) != 0)
		return ;
	temp = g_global.env;
	while (temp != 0)
	{
		kv = (t_kv *)temp->content;
		if (kv->value)
			printf("%s=%s\n", kv->name, kv->value);
		else
			printf("%s=\n", kv->name);
		temp = temp->next;
	}
}
