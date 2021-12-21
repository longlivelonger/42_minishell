/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:56:58 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/21 14:39:59 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	not_valid_name(char *name, char *command)
{
	if (!is_valid_env_key(name))
	{
		g_global.exit_status = 1;
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

void	builtin_export(char **args)
{
	t_kv	*kv;

	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "export", 7) != 0)
		return ;
	if (args[1] == 0)
		print_sorted_env();
	while ((++args)[0] != 0)
	{
		kv = create_env_variable(args[0]);
		if (kv == 0)
		{
			perror("export");
			g_global.exit_status = 1;
			continue ;
		}
		if (not_valid_name(kv->name, "export"))
		{
			free(kv->name);
			free(kv);
			continue ;
		}
		delete_env_variable(kv->name);
		ft_lstadd_back(&g_global.env, ft_lstnew(kv));
	}
}

void	builtin_unset(char **args)
{
	if (args == 0 || args[0] == 0 || ft_strncmp(args[0], "unset", 6) != 0)
		return ;
	while ((++args)[0] != 0)
	{
		if (not_valid_name(args[0], "unset"))
			continue ;
		delete_env_variable(args[0]);
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
		temp = temp->next;
	}
}
