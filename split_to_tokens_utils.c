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

int	check_quoted_sequence(char* str)
{
	int		local_count;
	char	q_type;

	local_count = 0;
	q_type = *str;
	while(*str)
	{
		local_count++;
		str++;
		if (*str == q_type)
			return (local_count);
	}
	return (0);
}

int	check_syntax(t_list *token_list);

int	expand_tokens(t_list *token_list)
{
	while (token_list)
	{
		if (((t_token *)token_list->content)->type == WORD)
		{
			
		}
	}
	
}

int	strip_quotes(t_list *token_list)
{
	while (token_list)
	{
		if (((t_token *)token_list->content)->type == S_QUOTE ||
			((t_token *)token_list->content)->type == D_QUOTE)
		token_list = token_list->next;
	}
	return (0);
}

