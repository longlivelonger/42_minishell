/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:33:31 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/22 14:53:20 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_zeros(char **envp, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		envp[i] = 0;
	}
}

char	**make_envp_array(void)
{
	t_list	*current;
	t_kv	*kv;
	char	**envp;
	int		i;
	char	*temp;

	current = g_global.env;
	envp = malloc((ft_lstsize(g_global.env) + 1) * sizeof(*envp));
	if (envp == 0)
		return (0);
	fill_zeros(envp, ft_lstsize(g_global.env) + 1);
	i = -1;
	while (current != 0)
	{
		kv = (t_kv *)current->content;
		if (kv->value)
		{
			temp = ft_strjoin(kv->name, "=");
			envp[++i] = ft_strjoin(temp, kv->value);
			free(temp);
		}
		current = current->next;
	}
	return (envp);
}

void	free_envp_array(char **envp)
{
	if (envp == 0)
		return ;
	while (envp[0] != 0)
	{
		free(envp[0]);
		envp++;
	}
}
