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

t_sc	*parse_simple_command(t_token token, t_sc *sc)
{
	t_sc	*new_sc;

	if (sc == NULL)
	{
		new_sc = malloc(sizeof(t_sc));
		new_sc->command_path = token->value;
		return new_sc;
	}
	else
	{
		sc->args_array = token->value;
		return (sc);
	}
}

t_com	*parse_command(t_list *token_list)
{
	t_com	*new_command;

	new_command = malloc(sizeof(t_com));
	new_command->sc = parse_simple_command(token_list, NULL);
	while (token_list->content->type != '|')
	{
		if (token_list->content->type == 1)
			new_command->sc = parse_simple_command(token_list, new_command->sc);
		else if (token_list->content->type == 1)
}

t_job	*parse_job(t_list *token_list)
{
	t_job	*new_job;

	while (token_list->content->type != ';' && token_list->content->type != '&')
	new_job = malloc(sizeof(t_job));
	new_job->com = parse_command(token_list);
}

int	build_stree(t_list *token_list)
{
	t_cl	*root;

	root = malloc(sizeof(t_cl));
	while (token_list->next != NULL)
	{
		root->job = parse_job(token_list);
	}
}
