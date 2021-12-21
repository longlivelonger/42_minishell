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

char	check_quoted_sequence(char *str)
{
	char	q_type;

	q_type = *str;
	while (*str)
	{
		str++;
		if (*str == q_type)
			return (q_type);
	}
	return ('\0');
}

int	count_quoted_expr(char *str, char *term_symbol, int	*count)
{
	if (*str == '"' || *str == 39)
	{
		if (*str == *term_symbol)
			*term_symbol = '\0';
		else if (!(*term_symbol))
		{
			*term_symbol = check_quoted_sequence(str);
			if (!(*term_symbol))
				return (1);
		}
	}
	else if (*str == '$' && *term_symbol != 39)
		return (count_env_value(str + 1, count));
	else
		return (1);
	return (0);
}

int	count_env_value(char *key, int *count)
{
	int		key_len;
	int		value_len;
	char	*value;

	key_len = 0;
	if ((key + key_len) && ((*(key + key_len) >= 48 && *(key + key_len) <= 57)))
		return (3);
	while ((key + key_len) && ((*(key + key_len) >= 97
				&& *(key + key_len) <= 122)
			|| (*(key + key_len) >= 65 && *(key + key_len) <= 90)))
		(key_len)++;
	*count += key_len;
	if (key_len == 0)
		return (0);
	key = ft_substr(key, 0, key_len);
	value = get_env(key);
	value_len = ft_strlen_adpt(value);
	free(key);
	return (value_len);
}

int	build_redirections(char type, t_com *new_command, t_list **token_list)
{
	if (type == '>' || type == 'G')
	{
		if (type == 'G')
			new_command->out_flag = O_APPEND;
		(*token_list) = (*token_list)->next;
		new_command->out = ((t_token *)(*token_list)->content)->value;
		return (1);
	}
	else if (type == '<' || type == 'L')
	{
		if (type == 'L')
			new_command->in_flag = 1;
		(*token_list) = (*token_list)->next;
		new_command->in = ((t_token *)(*token_list)->content)->value;
		return (1);
	}
	return (0);
}

int	ft_strlen_adpt(char	*str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (*(str + count))
		count++;
	return (count);
}
