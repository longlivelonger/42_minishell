/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:36:57 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/14 15:46:40 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env_content(void *content)
{
	t_env	*var;

	var = (t_env *)content;
	if (var->name != 0)
		free(var->name);
	if (var->value != 0)
		free(var->value);
}
