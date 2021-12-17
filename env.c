/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:36:57 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/17 12:54:38 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env_content(void *content)
{
	t_kv	*var;

	var = (t_kv *)content;
	if (var != 0 && var->name != 0)
		free(var->name);
	if (var != 0)
		free(var);
}

static t_kv	**make_array_from_list(t_list *lst)
{
	t_kv	**result;
	int		i;

	result = malloc((ft_lstsize(lst) + 1) * sizeof(*result));
	result[ft_lstsize(lst)] = 0;
	i = -1;
	while (lst != 0)
	{
		result[++i] = (t_kv *)lst->content;
		lst = lst->next;
	}
	return (result);
}

static void	sort_env_array(t_kv **arr, int size)
{
	int		i;
	int		sorted;
	t_kv	*temp;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (++i < size)
		{
			if (ft_strcmp(arr[i - 1]->name, arr[i]->name) > 0)
			{
				sorted = 0;
				temp = arr[i - 1];
				arr[i - 1] = arr[i];
				arr[i] = temp;
			}
		}
	}
}

void	print_sorted_env(void)
{
	t_kv	**arr;
	int		i;
	int		size;

	size = ft_lstsize(g_global.env);
	arr = make_array_from_list(g_global.env);
	sort_env_array(arr, size);
	i = -1;
	while (++i < size)
	{
		if (arr[i]->value != 0)
			printf("%s=\"%s\"\n", arr[i]->name, arr[i]->value);
		else
			printf("%s\n", arr[i]->name);
	}
	free(arr);
}

t_kv	*create_env_variable(char *str)
{
	t_kv	*var;

	var = malloc(sizeof(*var));
	if (var == 0)
		return (0);
	var->name = ft_strdup(str);
	var->value = 0;
	if (ft_strchr(var->name, '='))
	{
		var->value = ft_strchr(var->name, '=') + 1;
		*ft_strchr(var->name, '=') = '\0';
	}
	return (var);
}
