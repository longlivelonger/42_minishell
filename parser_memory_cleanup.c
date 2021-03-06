/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:54:29 by dweeper           #+#    #+#             */
/*   Updated: 2021/12/09 17:17:26 by dweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_list *tl)
{
	t_list	*temp;

	while (tl)
	{
		temp = tl;
		tl = tl->next;
		if (((t_token *)temp->content)->value)
			free(((t_token *)temp->content)->value);
		free((t_token *)temp->content);
		free(temp);
	}
}

static t_job	*free_job(t_job *job)
{
	t_job	*temp_job;

	if (job->com->is_path_alloc)
		free(job->com->command_path);
	if (job->com->args_array)
		free(job->com->args_array);
	if (job->com)
		free(job->com);
	temp_job = job->next_job;
	free(job);
	return (temp_job);
}

void	free_syntax_tree(t_cl *cl)
{
	t_job	*temp_job;

	if (cl)
	{
		temp_job = cl->job;
		while (temp_job)
		{
			temp_job = free_job(temp_job);
		}
		if (cl->and_cl)
			free_syntax_tree(cl->and_cl);
		if (cl->semicolon_cl)
			free_syntax_tree(cl->semicolon_cl);
		free(cl);
	}
}

int	extract_key(char *str)
{
	int	count;

	count = 0;
	while (*(str + count) && *(str + count) != '=')
		count++;
	return (count);
}
