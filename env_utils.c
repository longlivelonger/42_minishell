/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:17:23 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/17 12:55:03 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *name)
{
	t_list	*current;
	t_kv	*kv;

	current = g_global.env;
	while (current != 0)
	{
		kv = (t_kv *)current->content;
		if (ft_strcmp(kv->name, name) == 0)
			return (kv->value);
		current = current->next;
	}
	return (0);
}

int	is_valid_env_key(char *name)
{
	int	i;

	if (name == 0 || name[0] == '\0')
		return (0);
	i = -1;
	while (name[++i] != '\0')
	{
		if (i == 0 && ft_isdigit(name[i]))
			return (0);
		if (ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_')
			continue ;
		return (0);
	}
	return (1);
}

void	delete_env_variable(char *name)
{
	t_list	*prev;
	t_list	*current;

	prev = 0;
	current = g_global.env;
	while (current != 0)
	{
		if (ft_strcmp(((t_kv *)(current->content))->name, name) == 0)
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
