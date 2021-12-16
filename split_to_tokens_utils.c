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

char	check_quoted_sequence(char* str)
{
	//int		local_count;
	char	q_type;

	//local_count = 0;
	q_type = *str;
	while(*str)
	{
		//local_count++;
		str++;
		if (*str == q_type)
			return (q_type);
	}
	return ('\0');
}

int	check_syntax(t_list *token_list);

int	expand_tokens(t_list *token_list)
{
	while (token_list)
	{
		if (((t_token *)token_list->content)->type == WORD)
		{
			;
		}
		token_list = token_list->next;
	}
	return (0);
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

int	count_env_value(char *key, int *count)
{
	int	key_len;
	int	value_len;
	char	*fake_env[3];

	fake_env[0] = "PATH=/usr/bin:/123/123:test";
	fake_env[1] = "test=proverka123";
	fake_env[2] = "op=opaopaopapapa";
	key_len = *count;
	(*count)++;
	while ((key + *count) && ((*(key + *count) >=  97 && *(key + *count) <= 122) ||
		(*(key + *count) >=  65 && *(key + *count) <= 90)))
		(*count)++;
	if (key_len == 0)
		return (0);
	if (!find_env_value(key, key_len, fake_env, &value_len))
		return (0);
	else
		return (value_len);
}
