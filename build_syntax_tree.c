/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_stree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:18:30 by dweeper           #+#    #+#             */
/*   Updated: 2021/12/09 18:19:19 by dweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_command(char *str, char **com_path, char ***args_array)
{
	int	count;

	if (*com_path == NULL)
	{
		*com_path = str;
		*args_array = malloc(sizeof(char *) * 2);
		**args_array = str;
		*((*args_array) + 1) = NULL;
	}
	else
	{
		count = 0;
		while (*((*args_array) + count) != NULL)
			count++;
		*args_array = realloc(*args_array, sizeof(char *) * (count + 2));
		*((*args_array) + count) = str;
		*((*args_array) + count + 1) = NULL;
	}
}

static t_com	*init_command(void)
{
	t_com	*new_command;

	new_command = malloc(sizeof(t_com));
	new_command->command_path = NULL;
	new_command->in = NULL;
	new_command->out = NULL;
	new_command->in_flag = 0;
	new_command->out_flag = O_TRUNC;
	return (new_command);
}

static t_com	*parse_command(t_list *token_list, int max_count)
{
	t_com	*new_command;
	int		count;

	count = -1;
	new_command = init_command();
	while (++count < max_count)
	{
		if (build_redirections(((t_token *)token_list->content)->type,
				new_command, &token_list))
			count++;
		else
			build_command(((t_token *)token_list->content)->value,
				&new_command->command_path, &new_command->args_array);
		token_list = token_list->next;
	}
	return (new_command);
}

static t_job	*parse_job(t_list *token_list, int max_count)
{
	t_job	*new_job;
	t_list	*temp;
	int		count;

	temp = token_list;
	count = 0;
	while (count < max_count && ((t_token *)temp->content)->type != '|')
	{
		temp = temp->next;
		count++;
	}
	if (count < 1)
		return (NULL);
	new_job = malloc(sizeof(t_job));
	new_job->next_job = NULL;
	new_job->com = parse_command(token_list, count);
	if (count < max_count && ((t_token *)temp->content)->type == '|')
		new_job->next_job = parse_job(temp->next, max_count - count - 1);
	return (new_job);
}

t_cl	*parse_command_line(t_list *token_list)
{
	t_cl	*cl;
	t_list	*temp;
	int		count;

	temp = token_list;
	count = 0;
	while (temp && ((t_token *)temp->content)->type != ';'
		&& ((t_token *)temp->content)->type != '&')
	{
		count++;
		temp = temp->next;
	}
	if (count < 1)
		return (NULL);
	cl = malloc(sizeof(t_cl));
	cl->and_cl = NULL;
	cl->semicolon_cl = NULL;
	cl->job = parse_job(token_list, count);
	if (temp && ((t_token *)temp->content)->type == ';')
		cl->semicolon_cl = parse_command_line(temp->next);
	else if (temp && ((t_token *)temp->content)->type == '&')
		cl->and_cl = parse_command_line(temp->next);
	return (cl);
}
