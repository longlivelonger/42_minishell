/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:17:23 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/15 17:24:50 by sbronwyn         ###   ########.fr       */
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
